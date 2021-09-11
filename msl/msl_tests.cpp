///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2018 martysama0134. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////
#include <array>
#include <deque>
import <iostream>;
import <string>;
import <vector>;
using namespace std::string_literals;

//import "../include/msl/msl.h"; // instead of <msl/msl.h> for non-system headers analysing

import "../include/msl/bench.h";
import "../include/msl/cast.h";
import "../include/msl/check_assert.h";
import "../include/msl/file_ptr.h";
import "../include/msl/range.h";
import "../include/msl/utils.h";


constexpr bool EnableAllTests = true;
int main()
{
	// trim
	if constexpr (EnableAllTests)
	{
		std::cout << "### trim tests" << '\n';
		{
			auto s = "aa a a a "s;
			std::cout << '"' << msl::trim(s) << '"' << '\n';
			std::cout << '"' << msl::trim_in_place(s) << '"' << '\n';
		}
		{
			auto s = ""s;
			std::cout << '"' << msl::trim(s) << '"' << '\n';
			std::cout << '"' << msl::trim_in_place(s) << '"' << '\n';
		}
		{
			auto s = " a"s;
			std::cout << '"' << msl::trim(s) << '"' << '\n';
			std::cout << '"' << msl::trim_in_place(s) << '"' << '\n';
		}
		{
			auto s = "b "s;
			std::cout << '"' << msl::trim(s) << '"' << '\n';
			std::cout << '"' << msl::trim_in_place(s) << '"' << '\n';
		}
		{
			auto s = "  aaa bbb ccc        "s;
			std::cout << '"' << msl::trim(s) << '"' << '\n';
			std::cout << '"' << msl::trim_in_place(s) << '"' << '\n';
		}
		{
			auto s = "\n\n \n aaa  bbb  ccc  \t\t  \t   \t \n"s;
			std::cout << '"' << msl::trim(s) << '"' << '\n';
			std::cout << '"' << msl::trim_in_place(s) << '"' << '\n';
		}
		msl::bench([] {
			auto s = "\n\n \n aaa  bbb  ccc  \t\t  \t   \t \n"s;
			auto r = msl::trim(s);
		}); //142ms
		msl::bench([] {
			auto s = "\n\n \n aaa  bbb  ccc  \t\t  \t   \t \n"s;
			auto r = msl::trim_in_place(s);
		}); //99ms
	}
	// string_replace
	if constexpr (EnableAllTests)
	{
		std::cout << "### string_replace tests" << '\n';
		if constexpr (EnableAllTests)
		{
			msl::bench([] { auto r = msl::string_replace("a b c d", ' ', '.'); }); //53ms
			msl::bench([] { auto r = msl::string_replace("a b c d", " ", "."); }); //127ms
			msl::bench([] {
				auto r = "a b c d"s;
				msl::string_replace_in_place(r, ' ', '.');
			}); //27ms
			msl::bench([] {
				auto r = "a b c d"s;
				msl::string_replace_in_place(r, " ", ".");
			}); //100ms
		}
		if constexpr (EnableAllTests)
		{
			{
				auto s = "omae wa mou shindeiru"s;
				auto from = ' ';
				auto to = '.';
				auto r = s;
				msl::string_replace_in_place(r, from, to);
				msl::check_assert(r == "omae.wa.mou.shindeiru"s); // check if correct
				std::cout << r << '\n';
				msl::string_replace_in_place(r, to, from);
				msl::check_assert(s == r); // check the inverse as well
			}
			{
				auto s = "shinde kudasai"s;
				auto from = ' ';
				auto to = ',';
				auto r = s;
				msl::string_replace_in_place(r, from, to);
				msl::check_assert(r == "shinde,kudasai"s); // check if correct
				std::cout << r << '\n';
				msl::string_replace_in_place(r, to, from);
				msl::check_assert(s == r); // check the inverse as well
			}
		}
		if constexpr (EnableAllTests)
		{
			{
				auto s = "what is this a crossover episode?"s;
				auto from = ' ';
				auto to = '.';
				auto r = msl::string_replace(s, from, to);
				msl::check_assert(r == "what.is.this.a.crossover.episode?"s); // check if correct
				std::cout << r << '\n';
				msl::check_assert(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "what is this a crossover episode?"s;
				auto from = " "s;
				auto to = ","s;
				auto r = msl::string_replace(s, from, to);
				msl::check_assert(r == "what,is,this,a,crossover,episode?"s); // check if correct
				std::cout << r << '\n';
				msl::check_assert(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "what is this a crossover episode?"s;
				auto from = " "s;
				auto to = ";;;"s;
				auto r = msl::string_replace(s, from, to);
				msl::check_assert(r == "what;;;is;;;this;;;a;;;crossover;;;episode?"s); // check if correct
				std::cout << r << '\n';
				msl::check_assert(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "what;;;is;;;this;;;a;;;crossover;;;episode?"s;
				auto from = ";;;"s;
				auto to = ":::"s;
				auto r = msl::string_replace(s, from, to);
				msl::check_assert(r == "what:::is:::this:::a:::crossover:::episode?"s); // check if correct
				std::cout << r << '\n';
				msl::check_assert(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "whatOOOOisOOOOthisOOOOaOOOOcrossoverOOOOepisode?"s;
				auto from = "OOOO"s;
				auto to = "@@"s;
				auto r = msl::string_replace(s, from, to);
				msl::check_assert(r == "what@@is@@this@@a@@crossover@@episode?"s); // check if correct
				std::cout << r << '\n';
				msl::check_assert(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "what is this a crossover episode?"s;
				auto from = " "s;
				auto to = ""s;
				auto r = msl::string_replace(s, from, to);
				msl::check_assert(r == "whatisthisacrossoverepisode?"s); // check if correct
				std::cout << r << '\n';
				try
				{
					msl::check_assert(s == msl::string_replace(s, to, from)); // check the inverse as well
				}
				catch (const std::runtime_error &)
				{
				}
			}
			{
				auto s = "what is this a crossover episode?"s;
				auto from = " "s;
				auto to = ""s;
				try
				{
					auto r = msl::string_replace(s, from, to);
					msl::check_assert(r == "whatisthisacrossoverepisode?"s); // check if correct
					std::cout << r << '\n';
					msl::check_assert(s == msl::string_replace(s, to, from)); // check the inverse as well
				}
				catch (const std::runtime_error &)
				{
				}
			}
		}
	}
	// string_join
	if constexpr (EnableAllTests)
	{
		std::cout << "### string_join tests" << '\n';
		if constexpr (EnableAllTests)
		{
			msl::bench([] { auto a = msl::string_join({"1", "22", "333", "4444"}, ' '); });
			msl::bench([] { auto a = msl::string_join({"1", "22", "333", "4444"}, " "); });
		}
		if constexpr (EnableAllTests)
		{
			{
				std::vector<std::string> v = {"1", "22", "333", "4444"};
				auto t = ' ';
				auto s = msl::string_join(v, t);
				msl::check_assert(s == "1 22 333 4444"s); // check if correct
				std::cout << s << '\n';
				msl::check_assert(v == msl::string_split(s, t)); // check the inverse as well
			}
			{
				std::vector<std::string> v = {"1", "22", "333", "4444"};
				auto t = ";;;";
				auto s = msl::string_join(v, t);
				msl::check_assert(s == "1;;;22;;;333;;;4444"s); // check if correct
				std::cout << s << '\n';
				msl::check_assert(v == msl::string_split(s, t)); // check the inverse as well
			}
			{
				std::deque<std::string> v = {"1", "22", "333", "4444"};
				auto t = ".";
				auto s = msl::string_join(v, t);
				msl::check_assert(s == "1.22.333.4444"s); // check if correct
				std::cout << s << '\n';
				msl::check_assert(v == msl::string_split<std::deque<std::string>>(s, t)); // check the inverse as well
			}
			{
				std::array<std::string, 4> v = {"1", "22", "333", "4444"};
				auto t = "v";
				auto s = msl::string_join(v, t);
				msl::check_assert(s == "1v22v333v4444"s); // check if correct
				std::cout << s << '\n';
			}
		}
	}
	// string_split
	if constexpr (EnableAllTests)
	{
		std::cout << "### string_split tests" << '\n';
		if constexpr (EnableAllTests)
		{
			msl::bench([] { auto a = msl::string_split("this is sentence number 1", ' '); });
			msl::bench([] { auto a = msl::string_split("this is sentence number 1", " "); });
			msl::bench([] { auto a = msl::string_split_any("this is sentence number 1", " "); });
		}
		if constexpr (EnableAllTests)
		{
			{
				auto s = "this is sentence number 1"s;
				auto t = ' ';
				auto v = msl::string_split(s, t);
				std::vector<std::string> vc = {"this", "is", "sentence", "number", "1"};
				msl::check_assert(v == vc); // check if correct
				for (auto & s2 : v)
					std::cout << s2 << '\n';
				msl::check_assert(s == msl::string_join(v, t)); // check the inverse as well
			}
			{
				auto s = "this;;;is;;;sentence;;;number;;;2;;;;;;asd";
				auto t = ";;;";
				auto v = msl::string_split(s, t);
				std::vector<std::string> vc = {"this", "is", "sentence", "number", "2", "", "asd"};
				msl::check_assert(v == vc); // check if correct
				for (auto & s2 : v)
					std::cout << s2 << '\n';
				msl::check_assert(s == msl::string_join(v, t)); // check the inverse as well
			}
			{
				auto s = "this;;;is;;;sentence;;;number;;;2;;;;;;;;";
				auto t = ";;;";
				auto v = msl::string_split(s, t);
				std::vector<std::string> vc = {"this", "is", "sentence", "number", "2", "", ";;"};
				msl::check_assert(v == vc); // check if correct
				for (auto & s2 : v)
					std::cout << s2 << '\n';
				msl::check_assert(s == msl::string_join(v, t)); // check the inverse as well
			}
			{
				auto v = msl::string_split_any("this;is,big.boss", ";,.");
				std::vector<std::string> vc = {"this", "is", "big", "boss"};
				msl::check_assert(v == vc); // check if correct
				for (auto & s : v)
					std::cout << s << '\n';
			}
		}
	}
	// range tests
	if constexpr (EnableAllTests)
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
			std::cout << static_cast<int>(i) << '\n';
	}
	// file_ptr tests
	if constexpr (EnableAllTests)
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
		if constexpr (EnableAllTests)
		{
			msl::file_ptr p1("test.txt");
			msl::file_ptr p2(std::move(p1));
			std::cout << p1.get() << '\n';
			std::cout << p2.get() << '\n';
		}
	}
	// inherit_cast tests
	if constexpr (EnableAllTests)
	{
		std::cout << "### inherit_cast tests" << '\n';
		auto res = msl::inherit_cast<int>(3.4);
		std::cout << res << '\n';
		msl::check_assert(res == 3);
	}
	// truncate_cast tests
	if constexpr (EnableAllTests)
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
	if constexpr (EnableAllTests)
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
	if constexpr (EnableAllTests)
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
		if constexpr (EnableAllTests)
		{
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
				for (auto i = 0; i < 100; i++)
				{
				}
			});
		}
	}
	if constexpr (EnableAllTests)
	{
		if constexpr (EnableAllTests)
		{
			int a[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			msl::refill(a);
			for (auto & c : a)
				std::cout << c << '\n';
		}
		if constexpr (EnableAllTests)
		{
			char a[4]{'a', 'b', 'c', 'd'};
			msl::refill(a, 'e');
			for (auto & c : a)
				std::cout << c << '\n';
		}
		if constexpr (EnableAllTests)
		{
			struct AA
			{
				char a[20]{};
				int b{-1};
			};
			AA a[5]{
				{{}, 1}, {{}, 21}, {{}, 31}, {{}, 41}, {{}, 51},
			};
			for (auto & c : a)
				std::cout << c.b << '\n';
			msl::refill(a, AA());
			for (auto & c : a)
				std::cout << c.b << '\n';
		}
		if constexpr (EnableAllTests)
		{
			typedef struct AA
			{
				char a[20]{};
				int b{-1};
			} BB;
			BB a[3];
			msl::refill(a);
			std::cout << a[0].b << '\n';
		}
		if constexpr (EnableAllTests)
		{
			std::vector<char> a{'a', 'b', 'c', 'd'};
			msl::refill(a, '1');
			for (auto & c : a)
				std::cout << c << '\n';
		}
		if constexpr (EnableAllTests)
		{
			std::vector<int> a{1, 2, 3, 4};
			msl::refill(a, -1);
			for (auto & c : a)
				std::cout << c << '\n';
		}
		if constexpr (EnableAllTests)
		{
			std::array<int, 4> a{1, 2, 3, 4};
			msl::refill(a, -1);
			for (auto & c : a)
				std::cout << c << '\n';
		}
		if constexpr (EnableAllTests)
		{
			std::vector<std::string> a{"aaa", "bbb", "ccc", "ddd"};
			for (auto & c : a)
				std::cout << c << '\n';
			msl::refill(a, "eee");
			for (auto & c : a)
				std::cout << c << '\n';
		}
		if constexpr (EnableAllTests)
		{
			std::string a[4]{"aaa", "bbb", "ccc", "ddd"};
			for (auto & c : a)
				std::cout << c << '\n';
			msl::refill(a, "eee");
			for (auto & c : a)
				std::cout << c << '\n';
		}
	}

	std::cout << "All tests passed." << '\n';
	getchar();
	getchar();
	return 0;
}
