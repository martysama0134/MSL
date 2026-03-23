# Changelog

All notable changes to this project are documented in this file.

## [Unreleased]

### Added

- `observer_ptr` now supports `operator<=>` (defaulted), synthesizing `==`, `!=`, `<`, `<=`, `>`, `>=` — enables use in `std::set`, `std::unordered_set`, and sorted algorithms.
- New `msl::random_element(container)` returns `std::optional<value_type>` — a value-returning alternative to iterator-based `random_from`.
- `string_join` now accepts `std::initializer_list` arguments, fixing MSVC braced-init-list deduction failures.
- New test suites for `ptr`, `random`, and `bench` modules.
- Extended test coverage for `utils` (trim, string_replace, string_split_any, calculate_percentage, value_from_percentage) and `range` (irange, xrange edge cases).

### Changed

- `<msl/ptr.h>` now includes `<compare>` for three-way comparison support.
- `<msl/random.h>` now includes `<optional>` for `random_element` return type.

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

## [2.2.0] - 2025-02-09

### Added

- New `shared_pool` module for pooled shared-object lifetime management.
- Pool APIs now support variadic construction paths.
- Added `pool::debug_deallocate_all` for pool diagnostics/cleanup workflows.

### Changed

- Standardized header include guards and normalized include ordering across headers.

## [2.1.0] - 2025-02-08

### Changed

- Removed concepts as a hard requirement to improve compiler compatibility.

## [2.0.0] - 2025-02-07

### Added

- New smart-pointer utilities: `scoped_shared_ptr`, `observer_ptr`, and related no-owner pointer support.
- New range helpers: `enumerate` and `for_each_indexed`.
- New utility math helpers: `calculate_percentage` and `value_from_percentage`.

### Changed

- Refactored `range` internals and `file_ptr` internals.

### Fixed

- `string_split` vector output path now initializes defaults correctly.

## [1.4.3] - 2023-03-30

### Fixed

- Fixed `range` module interoperability with standard containers.

## [1.4.2] - 2023-01-24

### Added

- Added reverse-loop helper macro `MSL_FOR_RLOOP`.

## [1.4.1] - 2022-12-22

### Changed

- Updated `random.h` documentation coverage.

## [1.4.0] - 2022-12-12

### Changed

- Continued `std::string_view` refactor (part 2) across string/file interfaces.

## [1.3.9] - 2022-12-12

### Changed

- Expanded `MSL_FILE_PTR_ENABLE_WIDE_STRING` support with full wchar-to-char handling paths.

## [1.3.8] - 2022-12-12

### Changed

- Refactored string-oriented APIs toward `std::string_view` usage.

## [1.3.7] - 2022-12-11

### Changed

- Replaced `readline` naming with `getline` in `file_ptr` APIs.
- Reworked wide-string platform gating from `_WIN32` checks to `MSL_FILE_PTR_ENABLE_WIDE_STRING`.

## [1.3.6] - 2022-12-11

### Added

- Added `file_ptr` line-reading support and `MSL_FILE_PTR_ENABLE_STORE_FILENAME`.

## [1.3.5] - 2022-09-29

### Fixed

- Fixed warning around `test_error::what` override.

## [1.3.4] - 2022-06-20

### Fixed

- Resolved `min`/`max` conflicts when `windows.h` is included.

## [1.3.3] - 2022-06-15

### Added

- Added `MSL_FORCE_NOMINMAX` macro for Windows compatibility control.

## [1.3.2] - 2022-06-08

### Added

- Added `msl::avg_bench`.

### Changed

- Temporarily disabled `msl::test_assert` under `-fno-exceptions` configurations.

## [1.3.1] - 2022-06-05

### Added

- Added random-distribution validation tests.

### Changed

- Increased benchmark iterations and improved benchmark output clarity.
- Updated `MSL_FOR_LOOP` to use pre-increment iteration.

### Fixed

- Corrected default random-engine seeding/first-result behavior.

## [1.3.0] - 2022-06-04

### Added

- Introduced the random module (`random_number`, `random_real`, `random_from`, and related engine helpers).
- Added test/assert and benchmark helpers (`msl::test_assert`, `MSL_TEST_ASSERT`, `MSL_TEST_ASSERT_WN`, `msl::named_bench`, `MSL_FOR_LOOP`).
- Expanded `file_ptr` with wchar/wstring string-write support, stream/flush arguments, and simple fread wrappers.

### Changed

- Refactored `range`/`xrange` and `file_ptr` internals, including include-guard and test harness cleanup.

### Fixed

- Addressed Linux/non-Windows build issues, `fseek` warnings, `xrange` integer-step handling, and range template-specialization edge cases.

## [1.2.2] - 2019-05-03

### Changed

- Refactored `string_replace` internals.

## [1.2.1] - 2019-04-28

### Changed

- Documentation refresh in `README.md`.

## [1.2.0] - 2019-04-28

### Added

- Added `msl::trim`.

### Changed

- Improved trim implementation and simplified empty-string checks.

## [1.1.8] - 2018-09-11

### Added

- Added `msl::refill` support using free-function `begin/end` for generic containers.
- Extended `file_ptr` read/write pointer overload coverage (`char*`/`void*` paths).

### Fixed

- Fixed clang compatibility in `refill` (`typename value_type`) and refreshed Unix formatting/tooling patterns.

## [1.1.1] - 2018-08-24

### Added

- Added `msl::refill` for C arrays and standard containers.

## [1.0.9] - 2018-08-24

### Added

- Added `file_ptr` buffer-read/string-read helpers and accessor helpers (`get_ref`, `get_ptr`).

### Changed

- `file_ptr` constructors/open/reset paths now accept const string-reference inputs.
- Refined `file_ptr` reset/move behavior and implicit-conversion feature gating.

## [1.0.4] - 2018-08-23

### Added

- Added implicit `FILE*` conversion support for `file_ptr`.

## [1.0.3] - 2018-08-15

### Added

- Initial stabilized release of core utilities: `file_ptr`, `range`/`xrange`, `string_split`, `string_join`, `string_replace`, and cast helpers.
- Introduced early benchmark/test scaffolding and build-script support.

### Changed

- Refined header/template structure for utility APIs and improved cross-platform compiler settings.

### Fixed

- Fixed early `file_ptr` correctness issues (operators, move/swap/default ctor/dtor behavior) and multiple warning-level portability problems.
