# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What BenchGen is

BenchGen is a program synthesizer: it takes an L-System (a seed string + a set of production rules) and expands it into a compilable benchmark program. The expansion is parsed into an AST and then lowered by a language-specific code generator. The same AST is re-used to emit programs in any of the supported target languages (C, C++, Rust, Julia, Go, V, Carbon, Zig, Odin, D, MLIR).

The generator lives in `src/gen/`. The rest of `src/` (`Dalloc/`, `milepost/`, `perf/`, `scripts/`) contains independent tooling used around the generator — each has its own README.

## Build and run

All build/run happens inside `src/gen/`:

```bash
cd src/gen
make                          # builds the benchGen binary (clang++ by default, -std=c++20)
make clean                    # removes obj/ and the binary
./benchGen <iterations> <production_rules_file> <seed_string_file> <output_folder> <var_type> <language>
```

Valid `<var_type>`: `array`, `sortedlist`, `scalar` (see `src/gen/shared/consts.h`). Note that each language only implements a subset — inspect `src/gen/generator/factory.cpp` to see which `(language, var_type)` pairs actually return a variable (`nullptr` means unsupported). For example, MLIR only supports `scalar`; most other backends implement `array`.

Valid `<language>`: `c`, `cpp`, `rust`, `julia`, `go`, `v`, `carbon`, `zig`, `odin`, `d`, `mlir`.

Example inputs live in `src/gen/examples/ex0`..`ex9` and `src/gen/examples/mlir`, each containing a `production_rule.txt` and `seed_string.txt`.

## End-to-end test drivers

Shell scripts in `src/gen/` compile `benchGen`, run it against every `examples/ex*` directory, then build and execute each generated program with the target toolchain. Use these to smoke-test a backend after changes:

- `./zig_test_generator.sh` — generates, patches `build.zig` name to `benchmark`, runs `zig build run`.
- `./zig_test_generator_with_time.sh` — same plus timings, writes results to `zig_new_allocator_results.txt`.
- `./odin_test_generator.sh`, `./v_test_generator.sh` — equivalents for Odin and V.
- Outputs land in `zig_test_outputs/`, `odin_test_outputs/`, `v_test_outputs/` (wiped at start of each run).

There is no C/C++/Rust/etc. driver script — test those by running `./benchGen` directly on an example and building the generated program with its emitted Makefile / build file.

## Architecture

The pipeline in `CodeGeneratorDriver.cpp` is linear and the names below map 1:1 to directories under `src/gen/`:

1. **Lexer** (`lexer/`) tokenizes the seed file and the production-rules file into `Token`s (types in `shared/enums.h`: `TOK_IF`, `TOK_LOOP`, `TOK_CALL`, `TOK_NEW`, `TOK_INSERT`, `TOK_CONTAINS`, etc.).
2. **L-System** (`lSystem/`) rewrites the token stream for `<iterations>` rounds by applying production rules.
3. **Parser** (`parser/`) turns the expanded token stream into an AST of `Node` subclasses declared in `ast/languageAst.h`.
4. **Code generation**: `AST->gen(generator)` is called, where `generator` is a `ProgrammingLanguageGenerator` subclass selected by `ProgrammingLanguageGenerator::getGenerator(language, varType)` (in `generator/languageGenerator.cpp`).
5. **File emission**: `generator.generateFiles(bench_name)` writes the per-language source tree plus a Makefile / `build.zig` / `Cargo.toml` / etc. into `<output_folder>/`.

The AST nodes are language-agnostic — they call into a polymorphic `ProgrammingLanguageGenerator` interface (`addLine`, `startFunc`, `callFunc`, `addVar`, `freeVars`, `returnFunc`, `startScope`, `endScope`, `generateFiles`). There are two parallel class hierarchies you must keep in sync when adding a language:

- `ast/<lang>/<lang>Ast.{cpp,h}` — language-specific AST helpers (mostly unused for most languages; the shared `ast/languageAst.cpp` does the heavy lifting).
- `generator/<lang>/<lang>Generator.{cpp,h}` — lowers scope/function/loop/if/call/insert/remove/contains operations into concrete source text.
- `generator/<lang>/<lang>GeneratorVariable.{cpp,h}` — per-variable-type emitters (e.g. `CGeneratorArray`, `CGeneratorSortedList`, `MlirGeneratorScalar`). Instantiated by `generator/factory.cpp::VariableFactory::createVariable`.

Global state worth knowing about:
- `ProgrammingLanguage::LANGUAGE` (static, in `shared/consts.h`) is set in `main` before generation and read by the `VariableFactory` to decide which concrete variable class to instantiate. Don't refactor this away without threading the value through the factory, or the factory's `else if` chain will silently produce `nullptr`.
- `Parameters::ITERATIONS` and `Registers::REGISTER_COUNTER` are also static singletons in `shared/consts.h`.

## Adding a new target language

Every new language `X` requires edits in **all** of the following, otherwise the Makefile, driver switch, or factory will fail silently:

1. `shared/consts.h` — add `ProgrammingLanguage::X`.
2. `CodeGeneratorDriver.cpp` — add `X` to the validation `if` chain and the usage message.
3. `generator/languageGenerator.cpp::getGenerator` — dispatch to the new `XGenerator`.
4. `generator/factory.cpp::VariableFactory::createVariable` — dispatch variable creation for the `(X, varType)` combinations you support.
5. `ast/x/xAst.{cpp,h}` and `generator/x/xGenerator.{cpp,h}` + `generator/x/xGeneratorVariable.{cpp,h}`.
6. `Makefile` — add the three `.o` targets to `DEPS` and add the corresponding compile rules. The Makefile has no wildcard/auto-dependency rules, so missing entries produce link errors.

## Gotchas

- `ProgrammingLanguageGenerator::getGenerator` has a known bug: the branches for RUST, JULIA, GO, V, CARBON, ZIG, ODIN, D, MLIR compare against `ProgrammingLanguage::LANGUAGE` (the static) rather than the `language` parameter. It works because `main` sets `LANGUAGE` before calling `getGenerator`, but don't "fix" one branch without fixing them all.
- The driver requires 6 positional args but checks `argc < 6` (should be `< 7`); the sixth arg is read regardless. If you change the CLI, update the check and the usage string together.
- `obj/` is created on demand via `$(OBJ):` in the Makefile — don't remove that order-only prerequisite.
