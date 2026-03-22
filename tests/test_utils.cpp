#include "test_common.h"

#include <array>
#include <climits>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <msl/utils.h>

namespace
{
void test_split_string_empty_token()
{
    const auto parts = msl::string_split("abc", std::string{});
    MSL_EXPECT(parts.size() == 1);
    MSL_EXPECT(parts[0] == "abc");
}

void test_split_string_regular_token()
{
    const auto parts = msl::string_split("aa::bb::cc", std::string{"::"});
    MSL_EXPECT(parts.size() == 3);
    MSL_EXPECT(parts[0] == "aa");
    MSL_EXPECT(parts[1] == "bb");
    MSL_EXPECT(parts[2] == "cc");
}

void test_split_char_token()
{
    const auto parts = msl::string_split("1,2,3", ',');
    MSL_EXPECT(parts.size() == 3);
    MSL_EXPECT(parts[0] == "1");
    MSL_EXPECT(parts[1] == "2");
    MSL_EXPECT(parts[2] == "3");
}

void test_to_lower_in_place_and_copy()
{
    std::string text = "HeLLo-123!";
    msl::to_lower_in_place(text);
    MSL_EXPECT(text == "hello-123!");

    const auto lowered = msl::to_lower("MiXeD Case!");
    MSL_EXPECT(lowered == "mixed case!");
}

void test_format_grouped_number_default_separator()
{
    MSL_EXPECT(msl::format_grouped_number(0) == "0");
    MSL_EXPECT(msl::format_grouped_number(1234567) == "1.234.567");
    MSL_EXPECT(msl::format_grouped_number(-9876543) == "-9.876.543");
}

void test_format_grouped_number_custom_separator_and_limits()
{
    MSL_EXPECT(msl::format_grouped_number(1234567, ',') == "1,234,567");
    MSL_EXPECT(msl::format_grouped_number(LLONG_MAX, ',') == "9,223,372,036,854,775,807");
    MSL_EXPECT(msl::format_grouped_number(LLONG_MIN) == "-9.223.372.036.854.775.808");
}

void test_string_join_with_ranges()
{
    const std::vector<std::string> values = {"alpha", "beta", "gamma"};
    MSL_EXPECT(msl::string_join(values, ',') == "alpha,beta,gamma");
    MSL_EXPECT(msl::string_join(values, std::string{"::"}) == "alpha::beta::gamma");

    const std::array<std::string_view, 3> words = {"red", "green", "blue"};
    const std::span<const std::string_view> words_span(words);
    MSL_EXPECT(msl::string_join(words_span, ',') == "red,green,blue");

    const std::vector<char> chars = {'a', 'b', 'c'};
    MSL_EXPECT(msl::string_join(chars, ',') == "a,b,c");
}

void test_refill_uses_ranges_algorithms()
{
    int arr[4] = {1, 2, 3, 4};
    msl::refill(arr);
    MSL_EXPECT(arr[0] == 0 && arr[1] == 0 && arr[2] == 0 && arr[3] == 0);

    std::vector<int> values = {1, 2, 3};
    msl::refill(values, 7);
    MSL_EXPECT(values[0] == 7 && values[1] == 7 && values[2] == 7);
}

void test_string_join_with_initializer_list()
{
    MSL_EXPECT(msl::string_join({"1", "22", "333"}, ' ') == "1 22 333");
    MSL_EXPECT(msl::string_join({"a", "b", "c"}, std::string{"--"}) == "a--b--c");
}

void test_trim()
{
    MSL_EXPECT(msl::trim("") == "");
    MSL_EXPECT(msl::trim(" ") == "");
    MSL_EXPECT(msl::trim("  hello  ") == "hello");
    MSL_EXPECT(msl::trim("\t\n text \r\n") == "text");
    MSL_EXPECT(msl::trim("nowhitespace") == "nowhitespace");

    MSL_EXPECT(msl::ltrim("  left") == "left");
    MSL_EXPECT(msl::ltrim("right  ") == "right  ");
    MSL_EXPECT(msl::rtrim("right  ") == "right");
    MSL_EXPECT(msl::rtrim("  left") == "  left");
}

void test_trim_in_place()
{
    std::string s = "  both  ";
    msl::trim_in_place(s);
    MSL_EXPECT(s == "both");

    std::string l = "\thello";
    msl::ltrim_in_place(l);
    MSL_EXPECT(l == "hello");

    std::string r = "world\n";
    msl::rtrim_in_place(r);
    MSL_EXPECT(r == "world");
}

void test_trim_idempotent()
{
    const auto once = msl::trim("  x  ");
    const auto twice = msl::trim(once);
    MSL_EXPECT(once == twice);
}

void test_string_replace_char()
{
    MSL_EXPECT(msl::string_replace("a.b.c", '.', ',') == "a,b,c");
    MSL_EXPECT(msl::string_replace("noop", 'x', 'y') == "noop");
    MSL_EXPECT(msl::string_replace("", '.', ',') == "");

    std::string s = "hello";
    msl::string_replace_in_place(s, 'l', 'r');
    MSL_EXPECT(s == "herro");
}

void test_string_replace_string()
{
    MSL_EXPECT(msl::string_replace("aa::bb::cc", std::string{"::"},  std::string{"."}) == "aa.bb.cc");
    MSL_EXPECT(msl::string_replace("abc", std::string{"x"}, std::string{"y"}) == "abc");
    MSL_EXPECT(msl::string_replace("aaa", std::string{""}, std::string{"x"}) == "aaa");

    std::string s = "foo bar foo";
    msl::string_replace_in_place(s, std::string{"foo"}, std::string{"baz"});
    MSL_EXPECT(s == "baz bar baz");
}

void test_string_split_any()
{
    const auto parts = msl::string_split_any("a,b;c.d", ",;.");
    MSL_EXPECT(parts.size() == 4);
    MSL_EXPECT(parts[0] == "a");
    MSL_EXPECT(parts[1] == "b");
    MSL_EXPECT(parts[2] == "c");
    MSL_EXPECT(parts[3] == "d");

    const auto single = msl::string_split_any("hello", ",");
    MSL_EXPECT(single.size() == 1);
    MSL_EXPECT(single[0] == "hello");
}

void test_calculate_percentage()
{
    MSL_EXPECT(msl::calculate_percentage(50, 100) == 50.0);
    MSL_EXPECT(msl::calculate_percentage(0, 100) == 0.0);
    MSL_EXPECT(msl::calculate_percentage(100, 100) == 100.0);
    MSL_EXPECT(msl::calculate_percentage(0, 0) == 0.0);

    const auto fp = msl::calculate_percentage(1.0, 4.0);
    MSL_EXPECT(fp == 25.0);
    MSL_EXPECT(msl::calculate_percentage(0.0, 0.0) == 0.0);
}

void test_value_from_percentage()
{
    MSL_EXPECT(msl::value_from_percentage(200, 50) == 100.0);
    MSL_EXPECT(msl::value_from_percentage(100, 0) == 0.0);

    const auto fp = msl::value_from_percentage(200.0, 25.0);
    MSL_EXPECT(fp == 50.0);
}

void test_split_join_roundtrip()
{
    const std::vector<std::string> v = {"alpha", "beta", "gamma"};
    const auto joined = msl::string_join(v, ',');
    const auto split = msl::string_split(joined, ',');
    MSL_EXPECT(split == v);
}
} // namespace

void run_utils_tests()
{
    test_split_string_empty_token();
    test_split_string_regular_token();
    test_split_char_token();
    test_to_lower_in_place_and_copy();
    test_format_grouped_number_default_separator();
    test_format_grouped_number_custom_separator_and_limits();
    test_string_join_with_ranges();
    test_refill_uses_ranges_algorithms();
    test_string_join_with_initializer_list();
    test_trim();
    test_trim_in_place();
    test_trim_idempotent();
    test_string_replace_char();
    test_string_replace_string();
    test_string_split_any();
    test_calculate_percentage();
    test_value_from_percentage();
    test_split_join_roundtrip();
}
