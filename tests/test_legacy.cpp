#include "test_common.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include <msl/legacy.h>

namespace
{

void test_minmax_ordered_bounds()
{
    MSL_EXPECT(msl::minmax(0, 5, 10) == 5);
    MSL_EXPECT(msl::minmax(0, -3, 10) == 0);
    MSL_EXPECT(msl::minmax(0, 42, 10) == 10);
}

void test_minmax_swapped_bounds()
{
    MSL_EXPECT(msl::minmax(10, 5, 0) == 5);
    MSL_EXPECT(msl::minmax(10, -3, 0) == 0);
    MSL_EXPECT(msl::minmax(10, 42, 0) == 10);
}

void test_bind_wrappers()
{
    auto subtract = [](int lhs, int rhs)
    {
        return lhs - rhs;
    };

    const auto first_bound = msl::bind1st(subtract, 10);
    const auto second_bound = msl::bind2nd(subtract, 3);

    MSL_EXPECT(first_bound(4) == 6);
    MSL_EXPECT(second_bound(9) == 6);
}

void test_random_shuffle_wrappers()
{
    const std::vector<int> input = {1, 2, 3, 4, 5, 6};

    auto with_generator = input;
    std::mt19937 seeded_generator(1234);
    msl::random_shuffle(with_generator.begin(), with_generator.end(), seeded_generator);

    auto shuffled_copy = with_generator;
    std::sort(shuffled_copy.begin(), shuffled_copy.end());
    MSL_EXPECT(shuffled_copy == input);

    auto default_generator = input;
    msl::random_shuffle(default_generator.begin(), default_generator.end());
    std::sort(default_generator.begin(), default_generator.end());
    MSL_EXPECT(default_generator == input);
}

struct mem_fun_target
{
    int value = 0;

    void increment()
    {
        ++value;
    }
};

void test_void_mem_fun_wrappers()
{
    mem_fun_target target{};

    const auto pointer_invoker = msl::void_mem_fun(&mem_fun_target::increment);
    pointer_invoker(&target);
    MSL_EXPECT(target.value == 1);

    const auto reference_invoker = msl::void_mem_fun_ref(&mem_fun_target::increment);
    reference_invoker(target);
    MSL_EXPECT(target.value == 2);
}

} // namespace

void run_legacy_tests()
{
    test_minmax_ordered_bounds();
    test_minmax_swapped_bounds();
    test_bind_wrappers();
    test_random_shuffle_wrappers();
    test_void_mem_fun_wrappers();
}
