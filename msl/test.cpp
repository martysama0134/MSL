#include <msl/msl.h>

#include <iostream>
#include <string>
using namespace std::string_literals;

int main()
{
	// file_ptr tests
	{
		msl::file_ptr p("test.txt");
		std::cout << ((p.is_open()) ? "OPEN"s : "CLOSE"s) << '\n';
		msl::check_assert(p.is_open());
		std::cout << p.size() << '\n';
		msl::check_assert(p.size() == 3);
		std::cout << p.string_read() << '\n';
		std::cout << p.size() << '\n';
		msl::check_assert(p.size() == 3);
		std::cout << p.remain_size() << '\n';
		msl::check_assert(p.remain_size() == 0);
	}
	getchar();
	getchar();
	return 0;
}
