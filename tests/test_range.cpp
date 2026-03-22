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
void test_range_basic()
{
    int sum = 0;
    for (auto v : msl::irange(5))
        sum += v;
    MSL_EXPECT(sum == 10); // 0+1+2+3+4

    int sum2 = 0;
    for (auto v : msl::irange(3, 6))
        sum2 += v;
    MSL_EXPECT(sum2 == 12); // 3+4+5
}

void test_range_empty_when_min_ge_max()
{
    int count = 0;
    for ([[maybe_unused]] auto v : msl::irange(5, 5))
        ++count;
    MSL_EXPECT(count == 0);

    int count2 = 0;
    for ([[maybe_unused]] auto v : msl::irange(10, 3))
        ++count2;
    MSL_EXPECT(count2 == 0);
}

void test_xrange_basic()
{
    int sum = 0;
    for (auto v : msl::xirange(4))
        sum += v;
    MSL_EXPECT(sum == 6); // 0+1+2+3
}

void test_xrange_with_step()
{
    std::vector<int> vals;
    for (auto v : msl::xirange(2, 10, 3))
        vals.push_back(v);
    MSL_EXPECT(vals.size() == 3); // 2, 5, 8
    MSL_EXPECT(vals[0] == 2);
    MSL_EXPECT(vals[1] == 5);
    MSL_EXPECT(vals[2] == 8);
}

void test_xrange_empty_when_invalid()
{
    int count = 0;
    for ([[maybe_unused]] auto v : msl::xirange(5, 2))
        ++count;
    MSL_EXPECT(count == 0);
}
} // namespace

void run_range_tests()
{
    test_for_each_indexed_accepts_const_range();
    test_enumerate_accepts_const_span();
    test_range_basic();
    test_range_empty_when_min_ge_max();
    test_xrange_basic();
    test_xrange_with_step();
    test_xrange_empty_when_invalid();
}
