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
#ifdef WIN32
#include <windows.h> // test if there's include instability (e.g. naming collisions)
#endif

#include <array>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std::string_literals;

#include <msl/msl.h> // instead of <msl/msl.h> for non-system headers analysing

constexpr bool EnableAllTests = true;

void RunTests()
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
			msl::trim_in_place(s);
		}); //99ms
	}
	// string_replace
	if constexpr (EnableAllTests)
	{
		std::cout << "### string_replace tests" << '\n';
		{
			msl::named_bench("Replace Char", [] { auto r = msl::string_replace("a b c d", ' ', '.'); }); //53ms
			msl::named_bench("Replace String", [] { auto r = msl::string_replace("a b c d", " ", "."); }); //127ms
			msl::named_bench("Replace Char InPlace", [] {
				auto r = "a b c d"s;
				msl::string_replace_in_place(r, ' ', '.');
			}); //27ms
			msl::named_bench("Replace String InPlace", [] {
				auto r = "a b c d"s;
				msl::string_replace_in_place(r, " ", ".");
			}); //100ms
		}
		{
			{
				auto s = "omae wa mou shindeiru"s;
				auto from = ' ';
				auto to = '.';
				auto r = s;
				msl::string_replace_in_place(r, from, to);
				MSL_TEST_ASSERT_WN(r == "omae.wa.mou.shindeiru"s); // check if correct
				std::cout << r << '\n';
				msl::string_replace_in_place(r, to, from);
				MSL_TEST_ASSERT_WN(s == r); // check the inverse as well
			}
			{
				auto s = "shinde kudasai"s;
				auto from = ' ';
				auto to = ',';
				auto r = s;
				msl::string_replace_in_place(r, from, to);
				MSL_TEST_ASSERT_WN(r == "shinde,kudasai"s); // check if correct
				std::cout << r << '\n';
				msl::string_replace_in_place(r, to, from);
				MSL_TEST_ASSERT_WN(s == r); // check the inverse as well
			}
		}
		{
			{
				auto s = "what is this a crossover episode?"s;
				auto from = ' ';
				auto to = '.';
				auto r = msl::string_replace(s, from, to);
				MSL_TEST_ASSERT_WN(r == "what.is.this.a.crossover.episode?"s); // check if correct
				std::cout << r << '\n';
				MSL_TEST_ASSERT_WN(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "what is this a crossover episode?"s;
				auto from = " "s;
				auto to = ","s;
				auto r = msl::string_replace(s, from, to);
				MSL_TEST_ASSERT_WN(r == "what,is,this,a,crossover,episode?"s); // check if correct
				std::cout << r << '\n';
				MSL_TEST_ASSERT_WN(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "what is this a crossover episode?"s;
				auto from = " "s;
				auto to = ";;;"s;
				auto r = msl::string_replace(s, from, to);
				MSL_TEST_ASSERT_WN(r == "what;;;is;;;this;;;a;;;crossover;;;episode?"s); // check if correct
				std::cout << r << '\n';
				MSL_TEST_ASSERT_WN(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "what;;;is;;;this;;;a;;;crossover;;;episode?"s;
				auto from = ";;;"s;
				auto to = ":::"s;
				auto r = msl::string_replace(s, from, to);
				MSL_TEST_ASSERT_WN(r == "what:::is:::this:::a:::crossover:::episode?"s); // check if correct
				std::cout << r << '\n';
				MSL_TEST_ASSERT_WN(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "whatOOOOisOOOOthisOOOOaOOOOcrossoverOOOOepisode?"s;
				auto from = "OOOO"s;
				auto to = "@@"s;
				auto r = msl::string_replace(s, from, to);
				MSL_TEST_ASSERT_WN(r == "what@@is@@this@@a@@crossover@@episode?"s); // check if correct
				std::cout << r << '\n';
				MSL_TEST_ASSERT_WN(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "what is this a crossover episode?"s;
				auto from = " "s;
				auto to = ""s;
				auto r = msl::string_replace(s, from, to);
				MSL_TEST_ASSERT_WN(r == "whatisthisacrossoverepisode?"s); // check if correct
				std::cout << r << '\n';
				MSL_TEST_ASSERT_WN(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
			{
				auto s = "what is this a crossover episode?"s;
				auto from = " "s;
				auto to = ""s;
				auto r = msl::string_replace(s, from, to);
				MSL_TEST_ASSERT_WN(r == "whatisthisacrossoverepisode?"s); // check if correct
				std::cout << r << '\n';
				MSL_TEST_ASSERT_WN(s == msl::string_replace(s, to, from)); // check the inverse as well
			}
		}
	}
	// string_join
	if constexpr (EnableAllTests)
	{
		std::cout << "### string_join tests" << '\n';
		msl::bench([] { auto a = msl::string_join({"1", "22", "333", "4444"}, ' '); });
		msl::bench([] { auto a = msl::string_join({"1", "22", "333", "4444"}, " "); });

		{
			std::vector<std::string> v = {"1", "22", "333", "4444"};
			auto t = ' ';
			auto s = msl::string_join(v, t);
			MSL_TEST_ASSERT_WN(s == "1 22 333 4444"s); // check if correct
			std::cout << s << '\n';
			MSL_TEST_ASSERT_WN(v == msl::string_split(s, t)); // check the inverse as well
		}
		{
			std::vector<std::string> v = {"1", "22", "333", "4444"};
			auto t = ";;;";
			auto s = msl::string_join(v, t);
			MSL_TEST_ASSERT_WN(s == "1;;;22;;;333;;;4444"s); // check if correct
			std::cout << s << '\n';
			MSL_TEST_ASSERT_WN(v == msl::string_split(s, t)); // check the inverse as well
		}
		{
			std::deque<std::string> v = {"1", "22", "333", "4444"};
			auto t = ".";
			auto s = msl::string_join(v, t);
			MSL_TEST_ASSERT_WN(s == "1.22.333.4444"s); // check if correct
			std::cout << s << '\n';
			MSL_TEST_ASSERT_WN(v == msl::string_split<std::deque<std::string>>(s, t)); // check the inverse as well
		}
		{
			std::array<std::string, 4> v = {"1", "22", "333", "4444"};
			auto t = "v";
			auto s = msl::string_join(v, t);
			MSL_TEST_ASSERT_WN(s == "1v22v333v4444"s); // check if correct
			std::cout << s << '\n';
		}
	}
	// string_split
	if constexpr (EnableAllTests)
	{
		std::cout << "### string_split tests" << '\n';
		msl::named_bench("Split by Char", [] { auto a = msl::string_split("this is sentence number 1", ' '); });
		msl::named_bench("Split by String", [] { auto a = msl::string_split("this is sentence number 1", " "); });
		msl::named_bench("Split Any by String", [] { auto a = msl::string_split_any("this is sentence number 1", " "); });
		{
			auto s = "this is sentence number 1"s;
			auto t = ' ';
			auto v = msl::string_split(s, t);
			std::vector<std::string> vc = {"this", "is", "sentence", "number", "1"};
			MSL_TEST_ASSERT_WN(v == vc); // check if correct
			for (auto & s2 : v)
				std::cout << s2 << '\n';
			MSL_TEST_ASSERT_WN(s == msl::string_join(v, t)); // check the inverse as well
		}
		{
			auto s = "this;;;is;;;sentence;;;number;;;2;;;;;;asd";
			auto t = ";;;";
			auto v = msl::string_split(s, t);
			std::vector<std::string> vc = {"this", "is", "sentence", "number", "2", "", "asd"};
			MSL_TEST_ASSERT_WN(v == vc); // check if correct
			for (auto & s2 : v)
				std::cout << s2 << '\n';
			MSL_TEST_ASSERT_WN(s == msl::string_join(v, t)); // check the inverse as well
		}
		{
			auto s = "this;;;is;;;sentence;;;number;;;2;;;;;;;;";
			auto t = ";;;";
			auto v = msl::string_split(s, t);
			std::vector<std::string> vc = {"this", "is", "sentence", "number", "2", "", ";;"};
			MSL_TEST_ASSERT_WN(v == vc); // check if correct
			for (auto & s2 : v)
				std::cout << s2 << '\n';
			MSL_TEST_ASSERT_WN(s == msl::string_join(v, t)); // check the inverse as well
		}
		{
			auto v = msl::string_split_any("this;is,big.boss", ";,.");
			std::vector<std::string> vc = {"this", "is", "big", "boss"};
			MSL_TEST_ASSERT_WN(v == vc); // check if correct
			for (auto & s : v)
				std::cout << s << '\n';
		}
	}
	// range tests
	if constexpr (EnableAllTests)
	{
		std::cout << "### range tests int(5)" << '\n';
		for (auto i : msl::range<int>(5))
			std::cout << i << '\n';
		std::cout << "### range tests double(5)" << '\n';
		for (auto i : msl::range<double>(5))
			std::cout << i << '\n';
		std::cout << "### xrange test to 5" << '\n';
		for (auto i : msl::xrange<int>(5))
			std::cout << i << '\n';
		std::cout << "### xrange test 3 to 5" << '\n';
		for (auto i : msl::xrange<int>(3, 5))
			std::cout << i << '\n';
		std::cout << "### xrange test 2 to 5 by 0.5" << '\n';
		for (auto i : msl::xrange<double>(2.0, 5.0, 0.5))
			std::cout << i << '\n';
		std::cout << "### xrange test 5 to 10 by 2" << '\n';
		for (auto i : msl::xrange<int>(5, 10, 2))
			std::cout << i << '\n';
		std::cout << "### xllrange test 3 to 5" << '\n';
		for (auto i : msl::xllrange(3, 5))
			std::cout << static_cast<long long>(i) << '\n';
		std::cout << "### xcrange test 3 to 5" << '\n';
		for (auto i : msl::xcrange(3, 5))
			std::cout << static_cast<int>(i) << '\n';

		{
			std::cout << "### range indexed of {aaa,bbb,ccc,ddd}" << '\n';
			std::vector<std::string> vc{"aaa", "bbb", "ccc", "ddd"};
			msl::for_each_indexed(vc, [](size_t i, auto val) { std::cout << "Index " << i << ": " << val << '\n'; });
		}
	}
	// file_ptr tests
	if constexpr (EnableAllTests)
	{
		std::cout << "### file_ptr tests" << '\n';
		msl::file_ptr p("test.txt"); // open test.txt on read-mode

		std::cout << ((p.is_open()) ? "OPEN"s : "CLOSE"s) << '\n';
		MSL_TEST_ASSERT_WN(p.is_open()); // check if open

		std::cout << p.size() << '\n';
		MSL_TEST_ASSERT_WN(p.size() == 3); // check its size

		std::cout << p.string_read() << '\n';
		std::cout << p.size() << '\n';
		MSL_TEST_ASSERT_WN(p.size() == 3); // check its size after read

		std::cout << p.remain_size() << '\n';
		MSL_TEST_ASSERT_WN(p.remain_size() == 0); // check its remaining size after read

		{
			msl::file_ptr p1("test_write.txt", "w");
			const char * s1 = "kekw";
			p1.string_write(s1);
			const std::string s2 = "rekt";
			p1.string_write(s2);
		}

		{
			msl::file_ptr p1("test.txt");
			msl::file_ptr p2(std::move(p1));
			std::cout << p1.get() << '\n';
			std::cout << p2.get() << '\n';
		}

		{
			msl::file_ptr f("test_tabs.txt");
			#ifdef MSL_FILE_PTR_ENABLE_STORE_FILENAME
			std::cout << f.filename() << ((f.is_open()) ? " OPEN"s : " CLOSE"s) << '\n';
			#endif
			MSL_TEST_ASSERT_WN(f.is_open()); // check if open

			while (auto recvline = f.getline())
			{
				auto & line = *recvline;

				msl::rtrim_in_place(line);
				if (line.empty() || line[0] == '/' || line[0] == '#')
					continue;
				// puts(line.c_str());

				auto tokens = msl::string_split_any(line, " \t");
				if (tokens.size() < 2)
					continue;

				auto mapId = std::stoi(tokens[0]);
				auto mapName = tokens[1].c_str();
				printf("id %d, name %s\n", mapId, mapName);
			}
		}
	}
	// inherit_cast tests
	if constexpr (EnableAllTests)
	{
		std::cout << "### inherit_cast tests" << '\n';
		auto res = msl::inherit_cast<int>(3.4);
		std::cout << res << '\n';
		MSL_TEST_ASSERT_WN(res == 3);
	}
	// truncate_cast tests
	if constexpr (EnableAllTests)
	{
		std::cout << "### truncate_cast tests" << '\n';
		{
			auto res = msl::truncate_cast<int>(3.4);
			std::cout << res << '\n';
			MSL_TEST_ASSERT_WN(res == 3);
		}
		{
			auto res = msl::truncate<unsigned short>(255.55);
			std::cout << res << '\n';
			MSL_TEST_ASSERT_WN(res == 255);
		}
		{
			auto res = msl::truncate<double>(222.44);
			std::cout << res << '\n';
			MSL_TEST_ASSERT_WN(res == 222);
		}
		try
		{
			auto res = msl::truncate<unsigned short>(100000.66);
			std::cout << res << '\n';
			MSL_TEST_ASSERT_WN(res == 100000);
		}
		catch (msl::truncate_error & e)
		{
			std::cout << e.what() << '\n';
		}
	}
	// bench tests
	if constexpr (EnableAllTests)
	{
		msl::named_bench("Vec Iter by 1", [] {
			std::vector<double> m_vec;
			double min = 2;
			double max = 5;
			auto n = (max - min);
			m_vec.resize(static_cast<std::size_t>(n));
			for (auto & e : m_vec)
				e += min++;
		});
		msl::named_bench("Vec Iter by 0.5", [] {
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
		msl::named_bench("Vec Emplace by 0.5", [] {
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
			for (auto i : msl::xdrange(2.0, 5.0, 0.5))
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
		std::cout << "### xllrange test 2 to 5 by 1" << '\n';
		msl::bench([] {
			for (auto i : msl::xllrange(2, 5, 1))
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

		std::cout << "### MSL_FOR_LOOP test to 100" << '\n'; // 370ms
		msl::bench([] {
			MSL_FOR_LOOP(100) {
				i;
			}
		});
		std::cout << "### MSL_FOR_LOOP_VAR test to 100" << '\n'; // 93ms
		msl::bench([] {
			MSL_FOR_LOOP_VAR(100, l) {
				l;
			}
		});
		std::cout << "### MSL_FOR_LOOP_VAR_START test to 100" << '\n'; // 2ms
		msl::bench([] {
			MSL_FOR_LOOP_VAR_START(100 - 1, j, -1) {
				j;
			}
		});
		std::cout << "### MSL_FOR_RLOOP test print first 20" << '\n'; // 2ms
		MSL_FOR_RLOOP(20) {
			std::cout << i << ",";
		}
		std::cout << std::endl;
		std::cout << "### MSL_FOR_LOOP test print first 5" << '\n'; // 2ms
		MSL_FOR_LOOP(5llu) {
			std::cout << i << ",";
		}
		std::cout << std::endl;
	}
	if constexpr (EnableAllTests)
	{
		{
			std::cout << "### refill test a[10]" << '\n';
			int a[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			msl::refill(a);
			for (auto & c : a)
				std::cout << c << ',';
			std::cout << '\n';
		}
		{
			std::cout << "### refill test a[4] with 'e'" << '\n';
			char a[4]{'a', 'b', 'c', 'd'};
			msl::refill(a, 'e');
			for (auto & c : a)
				std::cout << c << ',';
			std::cout << '\n';
		}
		{
			std::cout << "### refill test AA[5] struct" << '\n';
			struct AA
			{
				char a[20]{};
				int b{-1};
			};
			AA a[5]{
				{{}, 1}, {{}, 21}, {{}, 31}, {{}, 41}, {{}, 51},
			};
			for (auto & c : a)
				std::cout << c.b << ',';
			std::cout << '\n';
			msl::refill(a, AA());
			for (auto & c : a)
				std::cout << c.b << ',';
			std::cout << '\n';
		}
		{
			std::cout << "### refill test single struct AA.b" << '\n';
			typedef struct AA
			{
				char a[20]{};
				int b{-1};
			} BB;
			BB a[3];
			msl::refill(a);
			std::cout << a[0].b << ',';
			std::cout << '\n';
		}
		{
			std::cout << "### refill test vector char a,b,c,d" << '\n';
			std::vector<char> a{'a', 'b', 'c', 'd'};
			msl::refill(a, '1');
			for (auto & c : a)
				std::cout << c << ',';
			std::cout << '\n';
		}
		{
			std::cout << "### refill test vector 1,2,3,4" << '\n';
			std::vector<int> a{1, 2, 3, 4};
			msl::refill(a, -1);
			for (auto & c : a)
				std::cout << c << ',';
			std::cout << '\n';
		}
		{
			std::cout << "### refill test std::array 1,2,3,4" << '\n';
			std::array<int, 4> a{1, 2, 3, 4};
			msl::refill(a, -1);
			for (auto & c : a)
				std::cout << c << ',';
			std::cout << '\n';
		}
		{
			std::cout << "### refill test vector aaa,bbb,ccc,ddd" << '\n';
			std::vector<std::string> a{"aaa", "bbb", "ccc", "ddd"};
			for (auto & c : a)
				std::cout << c << ',';
			std::cout << '\n';
			msl::refill(a, "eee");
			for (auto & c : a)
				std::cout << c << ',';
			std::cout << '\n';
		}
		{
			std::cout << "### refill test carray aaa,bbb,ccc,ddd" << '\n';
			std::string a[4]{"aaa", "bbb", "ccc", "ddd"};
			for (auto & c : a)
				std::cout << c << ',';
			std::cout << '\n';
			msl::refill(a, "eee");
			for (auto & c : a)
				std::cout << c << ',';
			std::cout << '\n';
		}
	}
	if constexpr (EnableAllTests)
	{
		{
			std::cout << "### random_int test 10 to 20" << '\n';
			auto rr = msl::gen_random_int(10, 20);
			std::cout << rr() << '\n';
			std::cout << rr() << '\n';
			std::cout << rr() << '\n';
			std::cout << rr() << '\n';
			std::cout << rr() << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';
			std::cout << msl::random_int(10, 20) << '\n';

			std::cout << "### random_real test 10 to 20" << '\n';
			std::cout << msl::random_real<double>(10, 20) << '\n';
			std::cout << msl::random_real<double>(10, 20) << '\n';
			std::cout << msl::random_real<double>(10, 20) << '\n';
			std::cout << msl::random_real<double>(10, 20) << '\n';
			std::cout << msl::random_real<double>(10, 20) << '\n';
			std::cout << msl::random_real<double>(10, 20) << '\n';
			std::cout << msl::random_real(10.0, 20.0) << '\n';

			std::cout << "### random_number test 10 to 20" << '\n';
			std::cout << msl::random_number<int>(10, 20) << " int " << '\n';
			std::cout << msl::random_number<double>(10, 20) << " double " << '\n';
			std::cout << msl::random_number<int>(10, 20) << " int " << '\n';
			std::cout << msl::random_number<double>(10, 20) << " double " << '\n';
			std::cout << msl::random_number<int>(10, 20) << " int " << '\n';
			std::cout << msl::random_number<double>(10, 20) << " double " << '\n';
			std::cout << msl::random_number(10, 20) << " int " << '\n';
			std::cout << msl::random_number(10, 20) << " int " << '\n';
			std::cout << msl::random_number(10.0, 20.0) << " double " << '\n';
			std::cout << msl::random_number(10.0, 20.0) << " double " << '\n';

			std::cout << "### random_from test (dog,cat,frog,bird,fish,squirrel) (vector)" << '\n';
			std::vector<std::string> vekku{
				"dog","cat","frog","bird","fish","squirrel"
			};
			std::cout << msl::random_from(vekku)->c_str() << '\n';
			std::cout << msl::random_from(vekku)->c_str() << '\n';
			std::cout << msl::random_from(vekku)->c_str() << '\n';
			std::cout << msl::random_from(vekku)->c_str() << '\n';
			std::cout << msl::random_from(vekku)->c_str() << '\n';
			std::cout << msl::random_from(vekku)->c_str() << '\n';

			std::cout << "### random_from test (dog,cat,frog,bird,fish,squirrel) (carray)" << '\n';
			const char* vekku2[]{
				"dog","cat","frog","bird","fish","squirrel"
			};
			std::cout << *msl::random_from(vekku2) << '\n';
			std::cout << *msl::random_from(vekku2) << '\n';
			std::cout << *msl::random_from(vekku2) << '\n';
			std::cout << *msl::random_from(vekku2) << '\n';

			std::cout << "### random_from test (dog,cat,frog,bird,fish,squirrel) (map)" << '\n';
			std::map<int, std::string> mappu1{
				{0, "dog"},
				{1, "cat"},
				{2, "frog"},
				{3, "bird"},
				{4, "fish"},
				{5, "squirrel"},
			};
			std::cout << msl::random_from(mappu1)->second << '\n';
			std::cout << msl::random_from(mappu1)->second << '\n';
			std::cout << msl::random_from(mappu1)->second << '\n';
			std::cout << msl::random_from(mappu1)->second << '\n';

			std::cout << "### random_from test (empty map)" << '\n';
			std::map<int, std::string> mappu2;
			if (auto it = msl::random_from(mappu2); it != mappu2.end())
				std::cout << it->second << '\n';
			else
				std::cout << "(empty)" << '\n';
			MSL_TEST_ASSERT("mappu2", mappu2.empty());
			//msl::test_assert("mappu2", mappu2.empty()); // inline alternative
			//MSL_TEST_ASSERT("!mappu2", !mappu2.empty()); //force fail

			std::cout << "### random distribution test (dog,cat,frog,bird,fish,squirrel)" << '\n';
			std::map<std::string, uint32_t> vekkuDist;
			MSL_FOR_LOOP(10000) {
				vekkuDist[*msl::random_from(vekku)]++;
			}
			for (auto& elem : vekkuDist) {
				std::cout << elem.first << ": " << elem.second << '\n';
			}
		}
	}
	if constexpr (EnableAllTests)
	{
		{
			std::cout << std::fixed << std::setprecision(3);
			std::cout << "### calculate_percentage(1000,1500)=" << msl::calculate_percentage(1000, 1500) << "%" << std::endl;
			std::cout << "### calculate_percentage(1500,1000)=" << msl::calculate_percentage(1500, 1000) << "%" << std::endl;
			std::cout << "### calculate_percentage(10000,1500)=" << msl::calculate_percentage(10000, 1500) << "%" << std::endl;
			std::cout << "### calculate_percentage(1000,15000)=" << msl::calculate_percentage(1000, 15000) << "%" << std::endl;
			std::cout << "### calculate_percentage(1000,10000)=" << msl::calculate_percentage(1000, 10000) << "%" << std::endl;
			std::cout << "### calculate_percentage(10000,1000)=" << msl::calculate_percentage(10000, 1000) << "%" << std::endl;
			std::cout << "### calculate_percentage(10'000'000,1000)=" << msl::calculate_percentage(10'000'000, 1000) << "%" << std::endl;
			std::cout << "### calculate_percentage(1000,10'000'000)=" << msl::calculate_percentage(1000, 10'000'000) << "%" << std::endl;
			std::cout << "### value_from_percentage(1000,50%)=" << msl::value_from_percentage(1000, 50) << std::endl;
		}
	}
	#ifdef MSL_FILE_PTR_ENABLE_WIDE_STRING
	if constexpr (EnableAllTests)
	{
		std::cout << "### file_ptr wide string conversion" << '\n';
		{
			const std::wstring ws = L"ħëłlö";
			auto conv = msl::file_ptr::w2s(ws);
			printf("%s %s\n", conv->c_str(), (conv) ? "SUCCESS" : "FAILED");
		}
		{
			const std::wstring ws = L"index👌2";
			auto conv = msl::file_ptr::w2s(ws);
			printf("%s %s\n", conv->c_str(), (conv) ? "SUCCESS" : "FAILED");
		}
		{
			const std::wstring ws = L"";
			auto conv = msl::file_ptr::w2s(ws);
			printf("%s %s\n", conv->c_str(), (conv) ? "SUCCESS" : "FAILED");
		}
	}
	#endif
}

void RunFailedTests() {
	MSL_TEST_ASSERT("ForceFail1", false);
}

void TestMixedMsl()
{
	std::cout << __FUNCTION__ << " test starting" << '\n';

	// MSL_RUN_TEST unwrapped code:
	if constexpr (false)
	{
		try {
			RunTests();
			std::cout << "All tests passed." << '\n';
		} catch (msl::test_error& e) {
			std::cout << e.what() << " test failed." << '\n';
		}
	}
	MSL_RUN_TEST(RunTests);

	MSL_RUN_TEST(RunFailedTests);
	MSL_RUN_TEST([]() { MSL_TEST_ASSERT("ForceFail2", false); });

	std::cout << std::endl << "Press enter to continue..." << std::endl;
	std::ignore = getchar();
	std::ignore = getchar();
}
