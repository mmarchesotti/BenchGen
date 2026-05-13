**Usage**:

```bash
python3 benchmark_languages.py                     # full sweep, all langs/depths/examples
python3 benchmark_languages.py --depths 4-5 --examples ex1 --languages c,zig    # quick test
python3 benchmark_languages.py --timeout 600 --output runs.csv --plot bench.png  # custom
```

**What it does:** for each `(language, depth, example)` triple it runs `./benchGen <depth> ... array <lang>`, builds the generated program (with the same `sed` patch on `build.zig` the existing zig driver uses), times only the executable run with `time.perf_counter`, then averages across the 10 examples per `(language, depth)` cell. Missing toolchains are detected via `shutil.which` and warned-and-dropped at startup; per-run failures land in the CSV as `status=build_fail`/`run_timeout`/etc. and are excluded from the mean. The plot is `figsize=(8, 8)`, every line uses `marker='o'`, and the legend is `loc="upper left"`.
