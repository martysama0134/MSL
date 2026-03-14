# Legacy API Map

This document tracks compatibility-focused APIs exposed from `<msl/legacy.h>`.

## Policy

- Legacy APIs are opt-in via explicit include (`#include <msl/legacy.h>`).
- Legacy APIs are exposed in `namespace msl` for source compatibility.
- `namespace std` extension APIs are not provided.
- Legacy APIs are retained in v4 and reviewed for potential removal or migration policy changes in future major versions.

## Implemented in `msl/legacy.h`

| Symbol | Status | Notes |
| --- | --- | --- |
| `msl::minmax` | Implemented | Clamp helper with auto-swapped bounds support. |
| `msl::bind1st` | Implemented | Compatibility wrapper for deprecated binder-style usage. |
| `msl::bind2nd` | Implemented | Compatibility wrapper for deprecated binder-style usage. |
| `msl::random_shuffle` | Implemented | Compatibility wrapper over `std::shuffle`. |
| `msl::void_mem_fun` | Implemented | Compatibility wrapper for removed mem_fun-style pointer invocation. |
| `msl::void_mem_fun_ref` | Implemented | Compatibility wrapper for removed mem_fun_ref-style reference invocation. |
