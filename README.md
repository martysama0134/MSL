# MSL
Marty(Sama0134) Support Library for C++17 (C++14 backward-compatible)

### What it contains
It includes:
- `<msl/bench.h>`
	- `msl::bench(func, tries = 10000)`; perform easy benchmark tests and print the result
	- `msl::evaluate(func, tries = 1)`; perform easy benchmark tests and return the ms
- `<msl/cast.h>`
	- `msl::truncate_cast<T>`; Truncate floating-point
	- `msl::truncate<T>`; Truncate floating-point and throw msl::truncate_error exception if check fails.
	- `msl::integral_cast<T>`; Truncate floating-point to integral and throw msl::truncate_error exception if check fails.
	- `msl::inherit_cast<T>`; static_cast vs dynamic_cast? inherit_cast!
- `<msl/check_assert.h>`
	- `msl::check_assert(condition)`; inline function for asserts (instead of macros)
- `<msl/file_ptr.h>` Smart pointer (wrapper) for FILE.
	- `msl::file_ptr(filename, mode = "r")`; open filename and take ownership.
	- `msl::file_ptr(FILE * f)`; take ownership of another FILE.
- `<msl/range.h>`
	- `msl::range<T>(&min = 0, max)`; perform for-range loop with no memory allocation (10x faster than xrange!)
	- `msl::xrange<T>(&min = 0, max, &diff = 1.0)`; perform for-range loop using a runtime generated vector
- `<msl/util.h>`
	- `msl::string_split(str, char token)`; split a string into a vector by providing a single delim character (2x faster than string version)
	- `msl::string_split(str, string token)`; split a string into a vector by providing the delim string
	- `msl::string_split_any(str, string tokens)`; split a string into a vector by providing any of the single delim characters
	- `msl::string_join(vector<string>, token)`; join all the vector elements with the token into a string
	- `msl::string_replace(str, char from, char to)`; replace all occurrences of 'from' to 'to' returning a new string (3x faster than string version)
	- `msl::string_replace(str, string from, string to)`; replace all occurrences of 'from' to 'to' returning a new string
	- `msl::string_replace_in_place(str, char from, char to)`; replace all occurrences of 'from' to 'to' in the input str
	- `msl::string_replace_in_place(str, string from, string to)`; replace all occurrences of 'from' to 'to' in the input str (3x faster than string version, 4x faster than copied replace)
	- `msl::refill(array, value=default())`; default/custom-initialize the specific c array
	- `msl::refill(container, value=default())`; default/custom-initialize the specific std container

### How to use it
```cpp
#include <msl/msl.h>
```

### Dependencies
No dependencies.

Each include is also self-contained and header-only.
