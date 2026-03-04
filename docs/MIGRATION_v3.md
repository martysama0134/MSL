# Migration Guide: v2.x to v3.0

This guide documents behavioral changes introduced for v3.0 quality and safety.

## 1) `msl::file_ptr` write-return semantics

### What changed

The following methods now report bytes written (not item-count semantics):

- `write(const std::vector<char>&)`
- `write(const void*, std::size_t)`
- `string_write(std::string_view)`

### Migration impact

Code that expected `0` or `1` from successful writes must be updated to compare against expected byte counts.

## 2) `msl::file_ptr::string_read(char[], n=0)`

### What changed

- `n == 0` is now a defined no-op.
- `n > 0` reads at most `n - 1` bytes and always null-terminates.

### Migration impact

Code relying on prior undefined behavior when `n == 0` must be removed.

## 3) `msl::integral_cast` and `msl::truncate` float-to-integral safety

### What changed

For floating-point to integral conversions, v3.0 now validates before casting:

- finite-only input (`NaN` / `inf` rejected)
- range checks against target type bounds
- exactness checks for `integral_cast` (fractional input rejected)

### Migration impact

Inputs previously producing undefined behavior or implementation-defined results now throw `msl::truncate_error`.

## 4) `msl::test_assert` restored

### What changed

`msl::test_assert(name, condition)` is restored in `assert.h` for compatibility with documented usage.

## 5) `<msl/util.h>` compatibility header

### What changed

`<msl/util.h>` now exists and forwards to `<msl/utils.h>`.

### Migration impact

No change required. Existing include paths continue to work.

## 6) Legacy Visual Studio path relocation (v3.1)

### What changed

Legacy Visual Studio solution/project and demo sources moved from repo root and `msl/` into:

- `legacy/vs/msl_tests.sln`
- `legacy/vs/msl/`

### Migration impact

Tooling/scripts that referenced old legacy paths should be updated to the new `legacy/vs/...` locations.
