#include "test_common.h"

#include <array>
#include <cstddef>
#include <span>
#include <vector>

#include <msl/range.h>

namespace
{
void test_for_each_indexed_accepts_const_range()
{
    const std::vector<int> values = {10, 20, 30};

    std::size_t index_sum = 0;
    int value_sum = 0;

    msl::for_each_indexed(values, [&](std::size_t index, int value) {
        index_sum += index;
        value_sum += value;
    });

    MSL_EXPECT(index_sum == 3);
    MSL_EXPECT(value_sum == 60);
}

void test_enumerate_accepts_const_span()
{
    const std::array<int, 4> values = {1, 2, 3, 4};
    const std::span<const int> values_span(values);

    std::size_t index_sum = 0;
    int value_sum = 0;
    for (auto [index, value] : msl::enumerate(values_span))
    {
        index_sum += index;
        value_sum += value;
    }

    MSL_EXPECT(index_sum == 6);
    MSL_EXPECT(value_sum == 10);
}
} // namespace

void run_range_tests()
{
    test_for_each_indexed_accepts_const_range();
    test_enumerate_accepts_const_span();
}
