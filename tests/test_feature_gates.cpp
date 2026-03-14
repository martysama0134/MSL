#include "test_common.h"

#include <format>
#include <ranges>
#include <string>
#include <vector>
#include <version>

#ifndef __cpp_lib_format
#error "__cpp_lib_format must be defined for MSL v4.0"
#endif

#ifndef __cpp_lib_ranges
#error "__cpp_lib_ranges must be defined for MSL v4.0"
#endif

static_assert(__cpp_lib_format >= 201907L, "MSL v4.0 requires C++20 std::format support");
static_assert(__cpp_lib_ranges >= 201911L, "MSL v4.0 requires C++20 std::ranges support");

namespace
{
void test_std_format_smoke()
{
    const auto out = std::format("{} + {} = {}", 2, 3, 5);
    MSL_EXPECT(out == "2 + 3 = 5");
}

void test_std_ranges_smoke()
{
    const std::vector<int> values = {1, 2, 3, 4, 5, 6};
    auto even = values | std::views::filter([](int value) {
        return (value % 2) == 0;
    });

    int sum = 0;
    for (int value : even)
        sum += value;

    MSL_EXPECT(sum == 12);
}
} // namespace

void run_feature_gate_tests()
{
    test_std_format_smoke();
    test_std_ranges_smoke();
}
