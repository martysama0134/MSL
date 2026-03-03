# Compatibility Policy

## Language and Toolchain Baseline

- Language level: C++20.
- Stability-first subset: prefer broadly stable C++20 features across target toolchains.
- Avoid hard dependency on unstable library areas unless guarded:
  - `std::format`
  - `std::ranges`

## Official Platforms

- Windows
- Linux
- FreeBSD

## Official Compiler Targets

- Visual Studio 2022 (MSVC v143)
- Clang 18+
- Linux default latest Debian preinstalled toolchain
- FreeBSD default `cc` / `c++` (Clang 18/19 on FreeBSD 14/15)

## API Compatibility

- Compatibility is preferred for existing APIs unless a break provides clear safety/correctness value.
- Breaking changes require migration notes in `docs/MIGRATION_v3.md`.
- `MSL_FOR_*` macros are supported public API.

## Validation Model

- Routine automation: GitHub Actions for Windows and Linux.
- Release validation: documented manual FreeBSD gate in `docs/RELEASE_VALIDATION.md`.
