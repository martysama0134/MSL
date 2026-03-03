# MSL

[![CI](https://github.com/martysama0134/MSL/actions/workflows/ci.yml/badge.svg)](https://github.com/martysama0134/MSL/actions/workflows/ci.yml)

MSL (Marty Support Library) is a header-only C++20 utility library focused on practical helpers with minimal integration friction.

## Feature Map

| Header | Purpose |
| --- | --- |
| `msl/assert.h` | Assert helpers and test exceptions (`check_assert`, `test_assert`, `test_error`). |
| `msl/bench.h` | Lightweight benchmarking/evaluation helpers. |
| `msl/cast.h` | Truncation/integral conversion helpers with checked paths. |
| `msl/file_ptr.h` | RAII wrapper around `FILE*` with read/write helpers. |
| `msl/macro.h` | Public `MSL_FOR_*` loop and test macros. |
| `msl/pool.h` | Thread-safe shared object pool (`shared_pool<T>`). |
| `msl/ptr.h` | Pointer ownership wrappers (`scoped_shared_ptr`, `no_owner`, `observer_ptr`). |
| `msl/random.h` | Random generators, number utilities, and container sampling. |
| `msl/range.h` | Range/xrange and indexed iteration helpers. |
| `msl/utils.h` | String and container utility helpers. |
| `msl/util.h` | Compatibility forwarding header to `msl/utils.h`. |
| `msl/msl.h` | Aggregate include for all MSL headers. |

## Installation

### 1) Manual include

Copy `include/msl/` into your include path and use:

```cpp
#include <msl/msl.h>
```

### 2) CMake FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
  MSL
  GIT_REPOSITORY https://github.com/martysama0134/MSL.git
  GIT_TAG main
)
FetchContent_MakeAvailable(MSL)

target_link_libraries(your_target PRIVATE msl::msl)
```

### 3) CMake install + `find_package`

Build/install:

```sh
cmake -S . -B build/install -DMSL_BUILD_TESTS=OFF
cmake --build build/install
cmake --install build/install --prefix /your/prefix
```

Consume:

```cmake
find_package(MSL CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE msl::msl)
```

## Compiler and Platform Support

| Platform | Compiler/toolchain | Status |
| --- | --- | --- |
| Windows | Visual Studio 2022 (MSVC v143) | First-class |
| Linux | Debian default latest preinstalled toolchain | First-class |
| Linux | Clang 18+ | First-class |
| FreeBSD 14/15 | Default `cc` / `c++` (Clang 18/19) | Release-gated manual validation |

MSL targets C++20 with a stability-first subset. `std::format` and `std::ranges` are treated as optional/incremental features, not mandatory baseline dependencies.

## Quick Start

### String helpers

```cpp
#include <msl/utils.h>
#include <iostream>

int main() {
    auto parts = msl::string_split("alpha::beta::gamma", "::");
    std::cout << parts.size() << "\n"; // 3
}
```

### Safe numeric conversion

```cpp
#include <msl/cast.h>

int main() {
    auto v = msl::integral_cast<int>(42.0); // ok
    // msl::integral_cast<int>(42.5); // throws msl::truncate_error
}
```

### Shared object pool

```cpp
#include <msl/pool.h>

struct Obj { int value{}; };

int main() {
    auto pool = msl::shared_pool<Obj>::create();
    auto h = pool->acquire();
    h->value = 123;
}
```

## API Notes and Safety Caveats

- `file_ptr`:
  - `open(std::string_view, ...)` now opens through owned null-terminated strings.
  - reopening via `open(...)` first closes any currently owned file handle.
  - byte-oriented write helpers return bytes written.
  - `string_read(char[], n)` is defined for `n == 0` (no-op) and always null-terminates for `n > 0`.
- `cast`:
  - checked floating-to-integral paths reject `NaN`, `inf`, out-of-range values, and fractional values for `integral_cast`.
- `shared_pool`:
  - `shared_pool<T>::handle::get()` now correctly returns `T*`.
  - `shared_pool` remains thread-safe via internal mutex-protected operations.
- `MSL_FOR_*` macros are supported public API.

## Build and Test

Presets:

```sh
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

Shell helpers:

```sh
./test_build.sh
./test_run.sh
```

CI runs deterministic tests from `tests/` only. Legacy demo-heavy test sources remain in `msl/test_*.cpp` for local/manual use.

## Versioning and Release Notes

- Current release target: `v3.0`.
- Changelog: [CHANGELOG.md](CHANGELOG.md)
- Migration notes: [docs/MIGRATION_v3.md](docs/MIGRATION_v3.md)
- Compatibility policy: [docs/COMPATIBILITY.md](docs/COMPATIBILITY.md)
- Release validation gate: [docs/RELEASE_VALIDATION.md](docs/RELEASE_VALIDATION.md)

## License

MSL is distributed under the MIT License. See [LICENSE](LICENSE).
