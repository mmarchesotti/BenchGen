#!/usr/bin/env python3
"""Sweep BenchGen across languages and L-System depths and plot execution times.

Generates a program for each (language, depth, example), builds it, runs it
under wall-clock timing, averages times across examples, and writes a square
pyplot figure with one same-marker line per language.
"""
from __future__ import annotations

import argparse
import csv
import os
import re
import shutil
import statistics
import subprocess
import sys
import time
from pathlib import Path

GEN_DIR = Path(__file__).resolve().parent.parent
BENCHGEN = GEN_DIR / "benchGen"
EXAMPLES_DIR = GEN_DIR / "examples"
RUNS_DIR = GEN_DIR / "benchmark_runs"
BENCH_NAME = "benchmark"

DEFAULT_LANGUAGES = ["c", "cpp", "rust", "julia", "go", "v", "carbon", "zig", "odin", "d", "nim", "ada"]
DEFAULT_DEPTHS = list(range(4, 12))


def patch_zig_build(out_dir: Path) -> None:
    build_zig = out_dir / "build.zig"
    if not build_zig.exists():
        return
    text = build_zig.read_text()
    patched = re.sub(r'\.name = ".*"', f'.name = "{BENCH_NAME}"', text)
    if patched != text:
        build_zig.write_text(patched)


def zig_build(out_dir: Path) -> list[str]:
    patch_zig_build(out_dir)
    return ["zig", "build"]


# Each entry: tools needed on PATH, build-command factory (returns argv list given out_dir),
# and the path of the produced binary relative to out_dir.
LANG_CONFIG: dict[str, dict] = {
    "c":      {"tools": ["make"],           "build": lambda d: ["make"],                                    "binary": BENCH_NAME},
    "cpp":    {"tools": ["make"],           "build": lambda d: ["make"],                                    "binary": BENCH_NAME},
    "rust":   {"tools": ["make", "cargo"],  "build": lambda d: ["make"],                                    "binary": BENCH_NAME},
    "julia":  {"tools": ["make", "julia"],  "build": lambda d: ["make"],                                    "binary": BENCH_NAME},
    "go":     {"tools": ["make", "go"],     "build": lambda d: ["make"],                                    "binary": BENCH_NAME},
    "v":      {"tools": ["make", "v"],      "build": lambda d: ["make"],                                    "binary": BENCH_NAME},
    "carbon": {"tools": ["make", "carbon"], "build": lambda d: ["make"],                                    "binary": BENCH_NAME},
    "zig":    {"tools": ["zig"],            "build": zig_build,                                             "binary": f"zig-out/bin/{BENCH_NAME}"},
    "odin":   {"tools": ["odin"],           "build": lambda d: ["odin", "build", "./src", f"-out:{BENCH_NAME}", "-o:aggressive"], "binary": BENCH_NAME},
    "d":      {"tools": ["make", "dmd"],    "build": lambda d: ["make"],                                    "binary": BENCH_NAME},
    "nim":    {"tools": ["make", "nim"],    "build": lambda d: ["make"],                                    "binary": BENCH_NAME},
    "ada":    {"tools": ["make", "gnatmake"], "build": lambda d: ["make"],                                  "binary": BENCH_NAME},
}


def parse_depths(spec: str) -> list[int]:
    if "-" in spec:
        lo, hi = spec.split("-", 1)
        return list(range(int(lo), int(hi) + 1))
    return [int(x) for x in spec.split(",")]


def parse_csv_list(spec: str) -> list[str]:
    return [s.strip() for s in spec.split(",") if s.strip()]


def discover_examples() -> list[str]:
    return sorted(
        p.name for p in EXAMPLES_DIR.glob("ex*")
        if p.is_dir()
        and (p / "production_rule.txt").exists()
        and (p / "seed_string.txt").exists()
    )


def ensure_benchgen() -> None:
    if BENCHGEN.exists():
        return
    print("benchGen not found, running `make` in src/gen/...", flush=True)
    subprocess.run(["make"], cwd=GEN_DIR, check=True)


def filter_installed_languages(languages: list[str]) -> list[str]:
    available = []
    for lang in languages:
        cfg = LANG_CONFIG[lang]
        missing = [t for t in cfg["tools"] if shutil.which(t) is None]
        if missing:
            print(f"WARN skipping {lang}: missing tool(s) {missing}", flush=True)
            continue
        available.append(lang)
    return available


def run_one(lang: str, depth: int, example: str, timeout: float, run_args: list[str] | None = None) -> tuple[str, float | None, str]:
    """Generate, build, and time a single (lang, depth, example). Returns (status, seconds, detail)."""
    out_dir = RUNS_DIR / lang / f"d{depth}" / example / BENCH_NAME
    if out_dir.exists():
        shutil.rmtree(out_dir)
    out_dir.parent.mkdir(parents=True, exist_ok=True)

    # benchGen's lexer opens input files via `"./" + fileName`, so it can only resolve
    # paths relative to its cwd. We invoke it with cwd=GEN_DIR and pass the inputs as
    # paths relative to that directory. The output folder may be absolute (the generator
    # uses std::filesystem, which handles absolute paths fine).
    rules = Path("examples") / example / "production_rule.txt"
    seed = Path("examples") / example / "seed_string.txt"

    gen_cmd = [str(BENCHGEN), str(depth), str(rules), str(seed), str(out_dir), "array", lang]
    try:
        subprocess.run(gen_cmd, cwd=GEN_DIR, check=True, capture_output=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return "gen_timeout", None, f"benchGen timeout after {timeout}s"
    except subprocess.CalledProcessError as e:
        return "gen_fail", None, e.stderr.decode(errors="replace")

    build_cmd = LANG_CONFIG[lang]["build"](out_dir)
    try:
        subprocess.run(build_cmd, cwd=out_dir, check=True, capture_output=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return "build_timeout", None, f"build timeout after {timeout}s"
    except subprocess.CalledProcessError as e:
        return "build_fail", None, e.stderr.decode(errors="replace")

    binary = out_dir / LANG_CONFIG[lang]["binary"]
    if not binary.exists():
        return "no_binary", None, f"missing {binary}"

    run_cmd = [str(binary)] + (run_args or [])
    start = time.perf_counter()
    try:
        subprocess.run(run_cmd, cwd=out_dir, check=True, capture_output=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return "run_timeout", None, f"run timeout after {timeout}s"
    except subprocess.CalledProcessError as e:
        return "run_fail", None, e.stderr.decode(errors="replace")
    elapsed = time.perf_counter() - start
    return "ok", elapsed, ""


def write_csv(path: Path, rows: list[dict]) -> None:
    with path.open("w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=["language", "depth", "example", "status", "seconds", "detail"])
        w.writeheader()
        for r in rows:
            out = dict(r)
            out["seconds"] = f"{r['seconds']:.6f}" if r["seconds"] is not None else ""
            detail = (r["detail"] or "")
            out["detail"] = detail[-200:].replace("\n", " | ")
            w.writerow(out)


def load_existing_results(path: Path) -> list[dict]:
    """Load rows previously written by write_csv. Returns [] if the file is missing."""
    if not path.exists():
        return []
    rows: list[dict] = []
    with path.open(newline="") as f:
        for row in csv.DictReader(f):
            try:
                depth = int(row["depth"])
            except (KeyError, ValueError):
                continue
            seconds_raw = row.get("seconds", "")
            try:
                seconds = float(seconds_raw) if seconds_raw else None
            except ValueError:
                seconds = None
            rows.append({
                "language": row.get("language", ""),
                "depth": depth,
                "example": row.get("example", ""),
                "status": row.get("status", ""),
                "seconds": seconds,
                "detail": row.get("detail", ""),
            })
    return rows


def aggregate(rows: list[dict], languages: list[str], depths: list[int]) -> dict[str, list[float | None]]:
    out: dict[str, list[float | None]] = {lang: [] for lang in languages}
    for lang in languages:
        for depth in depths:
            times = [r["seconds"] for r in rows if r["language"] == lang and r["depth"] == depth and r["status"] == "ok"]
            out[lang].append(statistics.mean(times) if times else None)
    return out


def plot(means: dict[str, list[float | None]], depths: list[int], path: Path) -> None:
    import matplotlib.pyplot as plt
    fig, ax = plt.subplots(figsize=(8, 8))
    plotted_any = False
    for lang, ys in means.items():
        if all(y is None for y in ys):
            continue
        plot_ys = [float("nan") if y is None else y for y in ys]
        ax.plot(depths, plot_ys, marker="o", label=lang)
        plotted_any = True
    if not plotted_any:
        print("WARN no successful runs to plot", flush=True)
        return
    ax.set_xlabel("Depth")
    ax.set_ylabel("Execution time (s)")
    ax.set_xticks(depths)
    ax.legend(loc="upper left")
    fig.tight_layout()
    fig.savefig(path, dpi=150)
    print(f"wrote plot {path}", flush=True)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--depths", default="4-11", help="depth range like '4-11' or comma list (default: 4-11)")
    ap.add_argument("--examples", default="", help="comma list (default: all examples/ex*)")
    ap.add_argument("--languages", default=",".join(DEFAULT_LANGUAGES), help="comma list (default: all 11)")
    ap.add_argument("--timeout", type=float, default=300.0, help="per-step timeout in seconds (default: 300)")
    ap.add_argument("--output", default="results.csv", help="CSV output path (default: results.csv)")
    ap.add_argument("--plot", default="benchmark.png", help="plot output path (default: benchmark.png)")
    ap.add_argument("--fail-fast", action="store_true", help="stop and exit non-zero on the first generate/build/run failure (implies --strict)")
    ap.add_argument("--strict", action="store_true", help="exit non-zero at the end if any combination failed")
    ap.add_argument("--no-plot", action="store_true", help="skip plotting (useful for smoke tests)")
    ap.add_argument("--loops-factor", type=int, default=None, help="pass -loops-factor N to each run (default: binary's own default)")
    ap.add_argument("--force", action="store_true", help="ignore cached results in --output and re-run every requested combination")
    args = ap.parse_args()

    os.chdir(GEN_DIR)
    ensure_benchgen()

    depths = parse_depths(args.depths)
    examples = parse_csv_list(args.examples) if args.examples else discover_examples()
    languages = filter_installed_languages(parse_csv_list(args.languages))

    if not examples:
        print("ERROR no examples found", file=sys.stderr)
        return 1
    if not languages:
        print("ERROR no languages with available toolchains", file=sys.stderr)
        return 1

    RUNS_DIR.mkdir(parents=True, exist_ok=True)

    output_path = Path(args.output)
    existing_rows = [] if args.force else load_existing_results(output_path)
    done_keys = {
        (r["language"], r["depth"], r["example"])
        for r in existing_rows if r["status"] == "ok"
    }

    new_rows: list[dict] = []
    total = len(languages) * len(depths) * len(examples)
    done = 0
    skipped = 0
    aborted = False
    for lang in languages:
        for depth in depths:
            for example in examples:
                done += 1
                if (lang, depth, example) in done_keys:
                    skipped += 1
                    print(f"[{done}/{total}] {lang} d={depth} {example}: cached, skipping", flush=True)
                    continue
                run_args = ["-loops-factor", str(args.loops_factor)] if args.loops_factor is not None else None
                status, seconds, detail = run_one(lang, depth, example, args.timeout, run_args)
                new_rows.append({
                    "language": lang, "depth": depth, "example": example,
                    "status": status, "seconds": seconds, "detail": detail,
                })
                tag = "ok" if status == "ok" else f"FAIL[{status}]"
                stime = f"{seconds:.3f}s" if seconds is not None else "--"
                print(f"[{done}/{total}] {lang} d={depth} {example}: {tag} {stime}", flush=True)
                if status != "ok" and args.fail_fast:
                    print(f"\n--- {lang} d={depth} {example}: {status} ---", flush=True)
                    print(detail, flush=True)
                    aborted = True
                    break
            if aborted:
                break
        if aborted:
            break

    new_keys = {(r["language"], r["depth"], r["example"]) for r in new_rows}
    merged = [r for r in existing_rows if (r["language"], r["depth"], r["example"]) not in new_keys] + new_rows
    merged.sort(key=lambda r: (r["language"], r["depth"], r["example"]))

    write_csv(output_path, merged)
    print(f"wrote {output_path}", flush=True)

    plot_languages = sorted({r["language"] for r in merged if r["status"] == "ok"})
    plot_depths = sorted({r["depth"] for r in merged if r["status"] == "ok"}) or depths
    means = aggregate(merged, plot_languages, plot_depths)

    if not args.no_plot and not aborted:
        plot(means, plot_depths, Path(args.plot))

    print("\n--- summary ---")
    summary_langs = sorted({r["language"] for r in merged})
    for lang in summary_langs:
        attempted = sum(1 for r in merged if r["language"] == lang)
        ok = sum(1 for r in merged if r["language"] == lang and r["status"] == "ok")
        print(f"  {lang}: {ok}/{attempted} successful runs")
    if skipped:
        print(f"  {skipped} combination(s) skipped (already cached in {output_path})")
    dropped = [l for l, ys in means.items() if all(y is None for y in ys)]
    if dropped:
        print(f"  dropped (no data): {', '.join(dropped)}")

    failures = [r for r in new_rows if r["status"] != "ok"]
    if failures and (args.strict or args.fail_fast):
        print(f"\n{len(failures)} failure(s) — exiting non-zero", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
