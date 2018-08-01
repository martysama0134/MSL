# MSL
Marty(Sama0134) Support Library for C++17

### What it contains
It includes:
- <msl/check_assert.h>
	- msl::check_assert; inline function for asserts (instead of macros)
- <msl/file_ptr.h>
	- msl::file_ptr; Smart pointer (wrapper) for FILE.
- <msl/inherit_cast.h>
	- msl::inherit_cast<T>; static_cast vs dynamic_cast conflictual? not anymore
- <msl/truncate_cast.h>
	- msl::truncate_cast<T>; Truncate floating-point
	- msl::truncate<T>; Truncate floating-point and throw msl::truncate_error exception if check fails.
	- msl::integral_cast<T>; Truncate floating-point to integral and throw msl::truncate_error exception if check fails.

### How to use it
```cpp
#include <msl/msl.h>
```

### Dependencies
No dependencies.
