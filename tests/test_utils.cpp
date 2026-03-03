#include "test_common.h"

#include <string>
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
} // namespace

void run_utils_tests()
{
    test_split_string_empty_token();
    test_split_string_regular_token();
    test_split_char_token();
}
