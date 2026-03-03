# Release Validation Gate

This document defines the required validation checks for a release candidate.

## Required CI Gate

The following GitHub Actions jobs must be green before tagging a release:

- `windows-msvc (VS2022)`
- `debian-default`
- `debian-clang`

The `alpine-clang` lane is intentionally non-blocking and can fail without blocking release.

## Required FreeBSD Manual Gate

Native FreeBSD CI is optional. For release, run the following on:

- FreeBSD 14.x (`c++` defaults to Clang 18 toolchain family)
- FreeBSD 15.x (`c++` defaults to Clang 19 toolchain family)

Commands:

```sh
cmake -S . -B build/freebsd-release -DMSL_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build/freebsd-release
ctest --test-dir build/freebsd-release --output-on-failure
```

Record for each FreeBSD run:

- FreeBSD version (`freebsd-version`)
- Compiler (`c++ --version`)
- CMake version (`cmake --version`)
- Test result summary

## Release Checklist

1. CI required lanes are green.
2. FreeBSD 14.x and 15.x manual validation logs are attached.
3. `README.md`, `CHANGELOG.md`, and `docs/MIGRATION_v3.md` are updated.
4. Tag creation is based on the validated commit SHA.
