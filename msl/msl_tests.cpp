#include <iostream>
#include <string>
using namespace std::string_literals;

#include "../include/msl/msl.h" // instead of <msl/msl.h> for non-system headers analysing

int main()
{
	// string_join
	if (false)
	{
		std::cout << "### string_join tests" << '\n';
		if (false)
		{
			msl::bench([] { auto a = msl::string_join({"1", "22", "333", "4444"}, ' '); });
			msl::bench([] { auto a = msl::string_join({"1", "22", "333", "4444"}, " "); });
		}
		if (false)
		{
			auto s1 = msl::string_join({"1", "22", "333", "4444"}, ' ');
			msl::check_assert(s1 == "1 22 333 4444"s);
			std::cout << s1 << '\n';
			auto s2 = msl::string_join({"1", "22", "333", "4444"}, ";;;");
			msl::check_assert(s2 == "1;;;22;;;333;;;4444"s);
			std::cout << s2 << '\n';
		}
	}
	// string_split
	if (false)
	{
		std::cout << "### string_split tests" << '\n';
		if (false)
		{
			msl::bench([] { auto a = msl::string_split("this is sentence number 1", ' '); });
			msl::bench([] { auto a = msl::string_split("this is sentence number 1", " "); });
			msl::bench([] { auto a = msl::string_split_any("this is sentence number 1", " "); });
		}
		if (false)
		{
			{
				auto v = msl::string_split("this is sentence number 1", ' ');
				std::vector<std::string> vc = {"this", "is", "sentence", "number", "1"};
				msl::check_assert(v == vc);
				for (auto & s : v)
					std::cout << s << '\n';
			}
			{
				auto v = msl::string_split("this;;;is;;;sentence;;;number;;;2;;;;;;asd", ";;;");
				std::vector<std::string> vc = {"this", "is", "sentence", "number", "2", "", "asd"};
				msl::check_assert(v == vc);
				for (auto & s : v)
					std::cout << s << '\n';
			}
			{
				auto v = msl::string_split("this;;;is;;;sentence;;;number;;;2;;;;;;;;", ";;;");
				std::vector<std::string> vc = {"this", "is", "sentence", "number", "2", "", ";;"};
				msl::check_assert(v == vc);
				for (auto & s : v)
					std::cout << s << '\n';
			}
			{
				auto v = msl::string_split_any("this;is,big.boss", ";,.");
				std::vector<std::string> vc = {"this", "is", "big", "boss"};
				msl::check_assert(v == vc);
				for (auto & s : v)
					std::cout << s << '\n';
			}
		}
	}
	// range tests
	if (false)
	{
		std::cout << "### range tests" << '\n';
		for (auto i : msl::range<int>(5))
			std::cout << i << '\n';
		std::cout << "### range tests" << '\n';
		for (auto i : msl::range<double>(5))
			std::cout << i << '\n';
		std::cout << "### xrange test to 5" << '\n';
		for (auto i : msl::xrange<int>(5))
			std::cout << i << '\n';
		std::cout << "### xrange test 3 to 5" << '\n';
		for (auto i : msl::xrange<int>(3, 5))
			std::cout << i << '\n';
		std::cout << "### xrange test 2 to 5 by 0.5" << '\n';
		for (auto i : msl::xrange<double>(2, 5, 0.5))
			std::cout << i << '\n';
		std::cout << "### xcrange test 3 to 5" << '\n';
		for (auto i : msl::xcrange(3, 5))
			std::cout << (int) i << '\n';
	}
	// file_ptr tests
	if (false)
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
	if (false)
	{
		std::cout << "### inherit_cast tests" << '\n';
		auto res = msl::inherit_cast<int>(3.4);
		std::cout << res << '\n';
		msl::check_assert(res == 3);
	}
	// truncate_cast tests
	if (false)
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
	// bench tests
	if (false)
	{
		msl::bench([] {
			std::vector<double> m_vec;
			double min = 2;
			double max = 5;
			auto n = (max - min);
			m_vec.resize(static_cast<std::size_t>(n));
			for (auto & e : m_vec)
			{
				e += min++;
			}
		});
		msl::bench([] {
			std::vector<double> m_vec;
			double min = 2;
			double max = 5;
			double diff = 0.5;
			auto n = (max - min) / diff;
			m_vec.resize(static_cast<std::size_t>(n));
			for (auto & e : m_vec)
			{
				e += min;
				min += diff;
			}
		});
		msl::bench([] {
			std::vector<double> m_vec;
			double min = 2;
			double max = 5;
			double diff = 0.5;
			for (auto n = min; n < max; n += diff)
				m_vec.emplace_back(n);
		});
	}
	if (false)
	{
		std::cout << "### range tests with bench" << '\n';
		std::cout << "### xirange test to 5" << '\n';
		msl::bench([] {
			for (auto i : msl::xirange(5))
				i;
		});
		std::cout << "### xirange test 3 to 5" << '\n';
		msl::bench([] {
			for (auto i : msl::xirange(3, 5))
				i;
		});
		std::cout << "### xdrange test 2 to 5 by 0.5" << '\n';
		msl::bench([] {
			for (auto i : msl::xdrange(2, 5, 0.5))
				i;
		});
		std::cout << "### xdrange test 2 to 5 by 1.0" << '\n';
		msl::bench([] {
			for (auto i : msl::xdrange(2, 5, 1))
				i;
		});
		std::cout << "### xirange test 2 to 5 by 1" << '\n';
		msl::bench([] {
			for (auto i : msl::xirange(2, 5, 1))
				i;
		});
		std::cout << "### xcrange test 2 to 5 by 1" << '\n';
		msl::bench([] {
			for (auto i : msl::xcrange(2, 5, 1))
				i;
		});
		std::cout << "### xcrange test 3 to 5" << '\n';
		msl::bench([] {
			for (auto i : msl::xcrange(3, 5))
				i;
		});
		std::cout << "### irange test to 5" << '\n';
		msl::bench([] {
			for (auto i : msl::irange(5))
				i;
		});
		std::cout << "### irange test 3 to 5" << '\n';
		msl::bench([] {
			for (auto i : msl::irange(3, 5))
				i;
		});
		std::cout << "### drange test 3 to 5" << '\n';
		msl::bench([] {
			for (auto i : msl::drange(3, 5))
				i;
		});
#if 0
		std::cout << "### xirange test to 100" << '\n'; // 370ms
		msl::bench([] {
			for (auto i : msl::xirange(100))
				i;
		});
		std::cout << "### irange test to 100" << '\n'; // 93ms
		msl::bench([] {
			for (auto i : msl::irange(100))
				i;
		});
		std::cout << "### normal for loop test to 100" << '\n'; // 2ms
		msl::bench([] {
			for (int i = 0; i < 100; i++)
				i;
		});
#endif
	}

	std::cout << "All tests passed." << '\n';
	getchar();
	getchar();
	return 0;
}
