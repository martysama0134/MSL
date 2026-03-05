#include <msl/msl.h>
#include <msl/legacy.h>

#include <random>
#include <vector>

namespace
{
struct no_exception_counter
{
    int value = 0;

    void increment()
    {
        ++value;
    }
};
} // namespace

int header_smoke_no_exceptions()
{
    msl::check_assert(true);
    msl::test_assert("no_exceptions", true);
    MSL_TEST_ASSERT("macro_no_exceptions", true);
    MSL_TEST_ASSERT_WN(true);

    const auto add_one = msl::bind1st(
        [](int lhs, int rhs)
        {
            return lhs + rhs;
        },
        1);

    std::vector<int> values = {1, 2, 3};
    std::mt19937 generator(42);
    msl::random_shuffle(values.begin(), values.end(), generator);

    no_exception_counter counter{};
    const auto ref_invoker = msl::void_mem_fun_ref(&no_exception_counter::increment);
    ref_invoker(counter);

    return msl::integral_cast<int>(42.0) + msl::minmax(0, 10, 5) + add_one(1) + counter.value + values.front();
}
