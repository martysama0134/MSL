# MSL
Marty(Sama0134) Support Library for C++17

### What it contains
It includes:
- `<msl/bench.h>`
	- msl::bench(lambda, args..., tries); perform easy benchmark tests and print the result
	- msl::evaluate(lambda, args..., tries); perform easy benchmark tests and return the ms
- `<msl/check_assert.h>`
	- msl::check_assert(condition); inline function for asserts (instead of macros)
- `<msl/file_ptr.h>` Smart pointer (wrapper) for FILE.
	- msl::file_ptr(filename, mode = "r"); open filename and take ownership.
	- msl::file_ptr(FILE * f); take ownership of another FILE.
- `<msl/inherit_cast.h>`
	- msl::inherit_cast<T>; static_cast vs dynamic_cast? inherit_cast!
- `<msl/range.h>`
	- msl::range<T>(&min = 0, max); perform for-range loop with no memory allocation (10x faster than xrange!)
	- msl::xrange<T>(&min = 0, max, &diff); perform for-range loop using a runtime generated vector
- `<msl/truncate_cast.h>`
	- msl::truncate_cast<T>; Truncate floating-point
	- msl::truncate<T>; Truncate floating-point and throw msl::truncate_error exception if check fails.
	- msl::integral_cast<T>; Truncate floating-point to integral and throw msl::truncate_error exception if check fails.

### How to use it
```cpp
#include <msl/msl.h>
```

### Dependencies
No dependencies.
