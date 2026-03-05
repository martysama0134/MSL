# Changelog

All notable changes to this project are documented in this file.

## [Unreleased]

## [3.1.1] - 2026-03-05

### Added

- New opt-in compatibility header `<msl/legacy.h>` with:
  - `msl::minmax`
  - `msl::bind1st`
  - `msl::bind2nd`
  - `msl::random_shuffle`
  - `msl::void_mem_fun`
  - `msl::void_mem_fun_ref`
- Legacy regression suite `tests/test_legacy.cpp` and header smoke `tests/headers/legacy.cpp`.
- `docs/LEGACY_API_MAP.md` to track implemented and deferred legacy candidates.

### Changed

- CMake project version is now `3.1.1`.
- README updated with legacy header feature entry and explicit legacy policy.
- No-exceptions header smoke now compiles and uses legacy APIs.

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

### Changed

- CMake project version is now `3.1.0` (release tag: `v3.1`).
- Legacy Visual Studio solution/project and demo files moved under `legacy/vs/`.
- README and release validation docs updated for the new layout, examples, and sanitizer gate.

### Fixed

- Removed tracked user-specific Visual Studio file `msl.vcxproj.user`.
- Updated legacy Visual Studio include paths after moving project files.
- Added ignore rules for user-specific Visual Studio files (`*.vcxproj.user`).

## [3.0.0] - 2026-03-03

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
