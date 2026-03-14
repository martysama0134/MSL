# Migration Guide: v3.x to v4.0

This guide documents behavior and platform baseline changes introduced in v4.0.

## 1) `msl::file_ptr` now supports both legacy and modern formatting

### What changed

v4.0 keeps legacy `printf` formatting and adds a new C++20 formatting path:

- Legacy style (unchanged): `file.write("%d %s", 42, "ok")`
- New style: `file.write_fmt("{} {}", 42, "ok")`

### Migration impact

No migration is required for existing `write("%...")` call sites.
Use `write_fmt` when you want `std::format` syntax and compile-time format checking.

## 2) C++20 library feature baseline is now mandatory

### What changed

MSL v4.0 requires:

- `std::format`
- `std::ranges`

These are no longer optional/incremental features.

### Migration impact

Compilers/standard libraries without both features in C++20 mode are no longer supported.

## 3) Linux CI baseline/toolchain changes

### What changed

Blocking Linux CI lanes now target explicit toolchain versions and STL variants:

- GCC 14 + libstdc++
- Clang 19 + libstdc++
- Clang 19 + libc++

### Migration impact

Consumers should align local/production toolchains with the same baseline to avoid divergence.
