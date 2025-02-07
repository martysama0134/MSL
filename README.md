# MSL
Marty(Sama0134) Support Library for C++20

### What it contains
It includes:
- `<msl/bench.h>`
	- `msl::avg_bench(func, tries = 10000, retries = 100)`; perform easy benchmark tests and print the result by average
	- `msl::avg_evaluate(func, tries = 10000, retries = 100)`; perform easy benchmark tests and return the ms by average
	- `msl::avg_named_bench(name, func, tries = 10000, retries = 100)`; same as bench, but with a name by average
	- `msl::bench(func, tries = 100000)`; perform easy benchmark tests and print the result
	- `msl::evaluate(func, tries = 100000)`; perform easy benchmark tests and return the ms
	- `msl::named_bench(name, func, tries = 100000)`; same as bench, but with a name
- `<msl/cast.h>`
	- `msl::truncate_cast<T>`; Truncate floating-point
	- `msl::truncate<T>`; Truncate floating-point and throw msl::truncate_error exception if check fails.
	- `msl::integral_cast<T>`; Truncate floating-point to integral and throw msl::truncate_error exception if check fails.
	- `msl::inherit_cast<T>`; static_cast vs dynamic_cast? inherit_cast!
- `<msl/assert.h>`
	- `msl::check_assert(condition)`; inline function for asserts (instead of macros)
	- `msl::test_assert(name, condition)`; inline function for test asserts (instead of macros)
	- `msl::test_error`; exception class for tests
- `<msl/file_ptr.h>` Smart pointer (wrapper) for FILE.
	- `msl::file_ptr`:
		- `file_ptr(string_view filename, mode = "r")`, `open(string_view filename, mode = "r")`; open filename and take ownership.
		- `file_ptr(wstring_view filename, mode = "r")`, `open(wstring_view filename, mode = "r")`; open filename and take ownership.
		- `file_ptr(FILE * f)`, `open(FILE * f, mode = "r")`; take ownership of another FILE.
		- `operator*()`, `operator->()`, `get()`, `get_ptr()`, `get_ref()`; returns the ptr of file
		- `operator!()`, `operator bool()`, `is_open()`; returns true if file ptr is not null
		- `close()`, `reset()`; close the file and reset the ptr
		- `reset(string_view filename, mode = "r")`; reset and open a new file
		- `reset(wstring_view filename, mode = "r")`; reset and open a new file
		- `reset(FILE * f)`; reset and take ownership of a new file
		- `release()`; release the file ptr
		- `size()`; return the whole file size
		- `remain_size()`; return the remaining file size to read
		- `write(vector<char> vec)`; write vector data into file
		- `write(buf, size)`; write buffer data into file
		- `string_write(string str)`; write string into file
		- `string_write(char * str)`; write zstring into file
		- `read(void * buf, &n = 0)`; read n bytes (0=all remaining) from file and store into buf
		- `vector<char> read(&n = 0)`; read n bytes (0=all remaining) from file and return it as vector
		- `string_read(void * buf, &n = 0)`; read n bytes (0=all remaining) from file and store into a null-terminated buf
		- `string string_read(&n = 0)`; read n bytes (0=all remaining) from file and return it as string
		- `getline(char delim = '\n')`; read a line ending with 'delim' from file and return it as string
		- `filename()`; return the filename
		- `wfilename()`; return the filename (windows only)
- `<msl/ptr.h>`
	- `msl::scoped_shared_ptr<T>`; wrapper of `std::shared_ptr` that can't be copied/moved outside the current scope
	- `msl::no_owner<T>`; wrapper of a raw pointer that can't be copied/moved outside the current scope
	- `msl::observer_ptr<T>`; a similar implementation of `std::experimental::observer_ptr`
- `<msl/macro.h>`
	- `MSL_FOR_LOOP(count)`; wrapper of `for (auto i = 0; i < count; ++i)`
	- `MSL_FOR_LOOP_VAR(count, varname)`; like MSL_FOR_LOOP but with `varname` instead of `i`
	- `MSL_FOR_LOOP_VAR_START(count, varname, start)`; like MSL_FOR_LOOP_VAR but with custom default `i` initialization
	- `MSL_FOR_RLOOP(count)`; reverse loop version of MSL_FOR_LOOP
	- `MSL_FOR_RLOOP_VAR(count, varname)`; reverse loop version of MSL_FOR_LOOP_VAR
	- `MSL_FOR_RLOOP_VAR_START(count, varname, start)`; reverse loop version of MSL_FOR_LOOP_VAR_START
	- `MSL_RUN_TEST(func)`; it runs the whole test case by passing a function / lambda
	- `MSL_TEST_ASSERT(name, condition)`; it checks a named test unit
	- `MSL_TEST_ASSERT_WN(condition)`; it checks an unnamed test unit
- `<msl/random.h>`
	- `msl::gen_random_number<T>(min = 0, max)`; it returns an instance to return random integral/real numbers between min and max
	- `msl::random_int<T>(min=<T>::min_value, max=<T>::max_value)`; pick a random integral number between min and max (min max included)
	- `msl::random_real<T>(min=<T>::min_value, max=<T>::max_value)`; pick a random floating point number between min and max (min max included)
	- `msl::random_number<T>(min=<T>::min_value, max=<T>::max_value)`; pick a random number (real/integral autodetected) a between min and max (min max included)
	- `msl::random_from<T>(container)`; picks a random element from container (both std container and c-array are supported)
- `<msl/range.h>`
	- `msl::range<T>(&min = 0, max)`; perform for-range loop with no memory allocation (10x faster than xrange!)
	- `msl::xrange<T>(&min = 0, max, &diff = 1.0)`; perform for-range loop using a runtime generated vector
   	- `msl::for_each_indexed(begin, end, func)`; perform for-range loop using a custom func(index, elem)
   	- `msl::for_each_indexed(container, func)`; perform for-range loop using a custom func(index, elem)
   	- `for (auto&& [i, elem] : msl::enumerate(container))`; perform for-each loop like python enumerate
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
	- `msl::trim(str, chars)`; also `msl::rtrim`, `msl::ltrim`, `msl::trim_in_place`, `msl::rtrim_in_place`, `msl::ltrim_in_place`, `msl::whitespaces`
   	- `msl::calculate_percentage(current, max)`; return the percentage of the difference of current and max
   	- `msl::value_from_percentage(amount, pct)`; apply and return the percentage to amount

### How to use it
```cpp
#include <msl/msl.h>
```

### Dependencies
No dependencies.

Each include is also self-contained and header-only.
