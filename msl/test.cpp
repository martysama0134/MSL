#include <iostream>
#include <msl/msl.h>
#include <string>
using namespace std::string_literals;

int main()
{
	// file_ptr tests
	{
		std::cout << "### file_ptr tests" << '\n';
		msl::file_ptr p("test.txt"); // open test.txt on read-mode

		std::cout << ((p.is_open()) ? "OPEN"s : "CLOSE"s) << '\n';
		msl::check_assert(p.is_open()); // check if open

		std::cout << p.size() << '\n';
		msl::check_assert(p.size() == 3); // check its size

		std::cout << p.string_read() << '\n';
		std::cout << p.size() << '\n';
		msl::check_assert(p.size() == 3); // check its size after read

		std::cout << p.remain_size() << '\n';
		msl::check_assert(p.remain_size() == 0); // check its remaining size after read
	}
	// inherit_cast tests
	{
		std::cout << "### inherit_cast tests" << '\n';
		auto res = msl::inherit_cast<int>(3.4);
		std::cout << res << '\n';
		msl::check_assert(res == 3);
	}
	getchar();
	getchar();
	return 0;
}
