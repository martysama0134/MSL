# Changelog

All notable changes to this project are documented in this file.

## [Unreleased]

### Added

- CMake-based build and test system with install/export package support.
- Deterministic CI-grade tests in `tests/`.
- Header smoke translation units for self-containment checks.
- Header-only exception configuration (`<msl/config.h>`) with `MSL_HAS_EXCEPTIONS` detection/override.
- GitHub Actions CI matrix for Windows (MSVC) and Linux (Debian default + Clang), with optional Alpine Clang lane.
- Compatibility forwarding header `<msl/util.h>`.
- Baseline project policy docs:
  - `docs/COMPATIBILITY.md`
  - `docs/MIGRATION_v3.md`
  - `docs/RELEASE_VALIDATION.md`

### Changed

- `test_build.sh` and `test_run.sh` now use CMake/CTest.
- Legacy `msl/test_*.cpp` tests no longer pause for interactive input.
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
