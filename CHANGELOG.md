# Changelog

All notable changes to this project are documented in this file.

## [Unreleased]

## [3.1.0] - 2026-03-04

### Added

- CMake option `MSL_BUILD_EXAMPLES` to compile optional example programs.
- Compile-verified `examples/` targets:
  - `msl_example_string_split`
  - `msl_example_safe_cast`
  - `msl_example_shared_pool`
  - `msl_example_file_ptr_io`
- Blocking Linux Clang ASan+UBSan CI lane (`linux-clang-asan-ubsan`) with dedicated `ci-linux-asan` preset.
- CI workflow hardening with explicit `permissions` and `concurrency` control.
- `legacy/README.md` documenting canonical CMake path versus legacy Visual Studio assets.
- Header-only exception configuration (`<msl/config.h>`) with `MSL_HAS_EXCEPTIONS` detection/override.
- Compatibility forwarding header `<msl/util.h>`.
- Baseline project policy docs:
  - `docs/COMPATIBILITY.md`
  - `docs/MIGRATION_v3.md`
  - `docs/RELEASE_VALIDATION.md`

### Changed

- CMake project version is now `3.1.0`.
- Legacy Visual Studio solution/project and demo files moved under `legacy/vs/`.
- `test_build.sh` and `test_run.sh` now use CMake/CTest.
- Legacy demo `test_*.cpp` sources no longer pause for interactive input.
- `file_ptr` write methods now use byte-count semantics for byte-oriented overloads.
- `file_ptr::open(std::string_view, ...)` now opens via owned null-terminated strings.

### Fixed

- `shared_pool::handle::get()` returned wrong pointer type.
- `shared_pool::handle` move constructor now moves `destroyer_`.
- `shared_pool::reserve()` / `prepare()` capacity reservation logic corrected.
- `assert`/`macro`/`cast`/`pool` throw paths now compile in `-fno-exceptions` builds (fail-fast abort semantics on error paths).
- `utils::string_split(str, tok_string)` now handles empty delimiters safely.
- `cast` floating-to-integral conversion paths now validate finite/range/truncation before cast.
- `file_ptr::string_read(char[], n)` now has defined and safe behavior for `n == 0`.
- `file_ptr::read(n)` now returns a vector resized to actual bytes read.

## [3.0.0] - 2026-03-03

### Planned Release Scope

- Build reliability first: reproducible CMake, deterministic tests, and CI matrix.
- Correctness and portability fixes in `pool.h`, `file_ptr.h`, `utils.h`, and `cast.h`.
- Publication and documentation baseline for professional OSS usage.
