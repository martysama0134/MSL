# Changelog

All notable changes to this project are documented in this file.

## [Unreleased]

## [4.0.0] - 2026-03-14

### Added

- New compile-time feature gate tests for C++20 `std::format` and `std::ranges` support.
- New range regression suite (`tests/test_range.cpp`) covering const ranges, spans, and `enumerate`/`for_each_indexed` usage.
- New CI toolchain probe executable (`msl_toolchain_info`) that reports compiler/STL and feature macro values.
- New migration guide `docs/MIGRATION_v4.md`.
- New Linux libc++ CI preset (`ci-linux-libcxx`).

### Changed

- CMake project version is now `4.0.0`.
- `file_ptr::write(fmt, args...)` keeps legacy `printf` formatting compatibility.
- New `file_ptr::write_fmt(fmt, args...)` adds C++20 `std::format` formatting.
- `utils` now provides `std::ranges`-constrained `string_join` overloads for string-like input ranges.
- `range` helpers now accept `std::ranges` input ranges, including const ranges.
- Blocking Linux CI lanes now pin explicit supported toolchains on Debian Trixie:
  - GCC 14 + libstdc++
  - Clang 19 + libstdc++
  - Clang 19 + libc++
- ASan/UBSan lane now pins Clang 18 on Ubuntu 24.04.
- Compatibility and release-validation docs updated for the v4 toolchain baseline.

## [3.2.0] - 2026-03-05

### Added

- New opt-in compatibility header `<msl/legacy.h>` with:
  - `msl::minmax`
  - `msl::bind1st`
  - `msl::bind2nd`
  - `msl::random_shuffle`
  - `msl::void_mem_fun`
  - `msl::void_mem_fun_ref`
- New `msl::traits` header `<msl/traits.h>` with:
  - `msl::traits::is_contiguous`
  - `msl::traits::is_contiguous_v`
  - `msl::traits::is_raw_v`
- New utility helpers in `<msl/utils.h>`:
  - `msl::to_lower_in_place`
  - `msl::to_lower`
  - `msl::format_grouped_number`
- Legacy regression suite `tests/test_legacy.cpp` and header smoke `tests/headers/legacy.cpp`.
- `docs/LEGACY_API_MAP.md` to track implemented legacy APIs.
- Trait regression suite `tests/test_traits.cpp` and header smoke `tests/headers/traits.cpp`.

### Changed

- CMake project version is now `3.2.0`.
- README updated with legacy header feature entry and explicit legacy policy.
- No-exceptions header smoke now compiles and uses legacy plus traits/utils APIs.
- `msl/msl.h` aggregate include now exports `traits.h`.
- Migration docs refreshed for current in-repo API guidance.

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
