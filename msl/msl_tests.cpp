#include <iostream>
#include <string>
using namespace std::string_literals;

#include "../include/msl/msl.h" // instead of <msl/msl.h> for non-system headers analysing

int main()
{
	// range tests
	{
		std::cout << "### range tests" << '\n';
		//for (auto i : msl::range<int>(5))
		//	printf("%x\n", i);
		std::cout << "### xrange test to 5" << '\n';
		for (auto i : msl::xrange<int>(5))
			printf("%x\n", i);
		std::cout << "### xrange test 3 to 5" << '\n';
		for (auto i : msl::xrange<int>(3, 5))
			printf("%x\n", i);
	}
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
	// truncate_cast tests
	{
		std::cout << "### truncate_cast tests" << '\n';
		{
			auto res = msl::truncate_cast<int>(3.4);
			std::cout << res << '\n';
			msl::check_assert(res == 3);
		}
		{
			auto res = msl::truncate<unsigned short>(255.55);
			std::cout << res << '\n';
			msl::check_assert(res == 255);
		}
		{
			auto res = msl::truncate<double>(222.44);
			std::cout << res << '\n';
			msl::check_assert(res == 222);
		}
		try
		{
			auto res = msl::truncate<unsigned short>(100000.66);
			std::cout << res << '\n';
			msl::check_assert(res == 100000);
		}
		catch (msl::truncate_error & e)
		{
			std::cout << e.what() << '\n';
		}
	}
	std::cout << "All tests passed." << '\n';
	getchar();
	getchar();
	return 0;
}
