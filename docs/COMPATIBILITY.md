# Compatibility Policy

## Language and Toolchain Baseline

- Language level: C++20.
- `std::format` is a required baseline dependency in v4.0+.
- `std::ranges` is a required baseline dependency in v4.0+.
- Consumers must use a standard library implementation that provides both features in C++20 mode.

## Exceptions Policy

- Exception-enabled builds are the default behavior.
- `-fno-exceptions` builds are supported for header compilation and usage.
- On error paths that normally throw, no-exceptions builds fail fast with `std::abort()`.
- `MSL_HAS_EXCEPTIONS` can be predefined (`0` or `1`) to override compiler auto-detection.

## Official Platforms

- Windows
- Linux
- FreeBSD

## Official Compiler Targets

- Visual Studio 2022 (MSVC v143)
- GCC 14+ (libstdc++)
- Clang 19+ with libstdc++ 14+ or libc++ 19+
- FreeBSD default `cc` / `c++` (Clang 18/19 on FreeBSD 14/15)

## API Compatibility

- Compatibility is preferred for existing APIs unless a break provides clear safety/correctness value.
- Breaking changes require migration notes in `docs/MIGRATION_v4.md`.
- `MSL_FOR_*` macros are supported public API.

## Validation Model

- Routine automation: GitHub Actions for Windows and Linux.
- Release validation: documented manual FreeBSD gate in `docs/RELEASE_VALIDATION.md`.
