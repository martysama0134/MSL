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
}
