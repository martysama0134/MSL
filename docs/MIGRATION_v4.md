# Migration Guide: v3.x to v4.0

This guide documents behavior and platform baseline changes introduced in v4.0.

## 1) `msl::file_ptr::write` format syntax change (breaking)

### What changed

The formatted overload now uses C++20 `std::format` syntax:

- Old style: `file.write("%d %s", 42, "ok")`
- New style: `file.write("{} {}", 42, "ok")`

The printf-style formatted backend has been removed from `file_ptr::write`.

### Migration impact

Call sites that used `%` specifiers must be updated to `{}` format strings.

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
