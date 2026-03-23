# Migration Guide: v3.x to v4.x

This guide documents behavior and platform baseline changes introduced in v4.x.

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

## 4) `observer_ptr` now supports comparison operators (v4.1)

### What changed

`msl::observer_ptr<T>` now provides a defaulted `operator<=>`, which synthesizes all six comparison operators (`==`, `!=`, `<`, `<=`, `>`, `>=`). This enables direct use in ordered and unordered associative containers.

`<msl/ptr.h>` now includes `<compare>`.

### Migration impact

No breaking change. Code that previously used manual `std::hash` workarounds or raw `.get()` comparisons can now use operators directly.

## 5) New `random_element` value-returning API (v4.1)

### What changed

`msl::random_element(container)` returns `std::optional<value_type>` — a copied value for non-empty containers, `std::nullopt` for empty ones. This complements the existing `random_from` which returns an iterator.

`<msl/random.h>` now includes `<optional>`.

### Migration impact

No breaking change. Existing `random_from` call sites are unaffected. Use `random_element` when you want a value directly without iterator dereferencing.

## 6) `string_join` accepts braced-init-lists (v4.1)

### What changed

New `std::initializer_list<T>` overloads for `string_join` allow calling with braced-init-lists:

```cpp
auto s = msl::string_join({"a", "b", "c"}, ","); // now works on MSVC
```

### Migration impact

No breaking change. Fixes MSVC template deduction failure when passing braced-init-lists directly.
