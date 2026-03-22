#include "test_common.h"

#include <set>
#include <vector>

#include <msl/random.h>

namespace
{
void test_random_int_in_range()
{
    for (int i = 0; i < 100; ++i)
    {
        const auto val = msl::random_int<int>(0, 10);
        MSL_EXPECT(val >= 0 && val <= 10);
    }
}

void test_random_real_in_range()
{
    for (int i = 0; i < 100; ++i)
    {
        const auto val = msl::random_real<double>(0.0, 1.0);
        MSL_EXPECT(val >= 0.0 && val < 1.0);
    }
}

void test_random_number_integral()
{
    for (int i = 0; i < 100; ++i)
    {
        const auto val = msl::random_number<int>(5, 15);
        MSL_EXPECT(val >= 5 && val <= 15);
    }
}

void test_random_number_floating()
{
    for (int i = 0; i < 100; ++i)
    {
        const auto val = msl::random_number<double>(-1.0, 1.0);
        MSL_EXPECT(val >= -1.0 && val < 1.0);
    }
}

void test_gen_random_number_class()
{
    msl::gen_random_int gen(1, 6);
    for (int i = 0; i < 100; ++i)
    {
        const auto val = gen();
        MSL_EXPECT(val >= 1 && val <= 6);
    }
}

void test_random_from_container()
{
    const std::vector<int> items = {10, 20, 30, 40, 50};
    std::set<int> seen;
    for (int i = 0; i < 200; ++i)
    {
        auto it = msl::random_from(items);
        MSL_EXPECT(it != items.end());
        seen.insert(*it);
    }
    // with 200 draws from 5 elements, extremely unlikely to miss any
    MSL_EXPECT(seen.size() == 5);
}

void test_random_from_empty()
{
    const std::vector<int> empty;
    auto it = msl::random_from(empty);
    MSL_EXPECT(it == empty.end());
}

void test_random_int_produces_variety()
{
    std::set<int> seen;
    for (int i = 0; i < 100; ++i)
        seen.insert(msl::random_int<int>(0, 99));
    // 100 draws from [0,99] should produce at least 10 distinct values
    MSL_EXPECT(seen.size() >= 10);
}
} // namespace

void run_random_tests()
{
    test_random_int_in_range();
    test_random_real_in_range();
    test_random_number_integral();
    test_random_number_floating();
    test_gen_random_number_class();
    test_random_from_container();
    test_random_from_empty();
    test_random_int_produces_variety();
}
