# Release Validation Gate

This document defines the required validation checks for a release candidate.

## Required CI Gate

The following GitHub Actions jobs must be green before tagging a release:

- `windows-msvc (VS2022)`
- `linux-gcc14-libstdcxx`
- `linux-clang19-libstdcxx`
- `linux-clang19-libcxx`
- `linux-clang-asan-ubsan`

The `alpine-clang` lane is intentionally non-blocking and can fail without blocking release.
All blocking lanes must emit successful toolchain probe output (`msl.toolchain_info`) including
`__cpp_lib_format` and `__cpp_lib_ranges`.

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
3. `README.md`, `CHANGELOG.md`, `docs/COMPATIBILITY.md`, and `docs/MIGRATION_v4.md` are updated.
4. Tag creation is based on the validated commit SHA.
