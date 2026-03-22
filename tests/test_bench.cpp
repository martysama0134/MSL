#include "test_common.h"

#include <msl/bench.h>

namespace
{
void test_evaluate_returns_nonnegative()
{
    auto duration = msl::evaluate([] { volatile int x = 0; (void)x; }, 10);
    MSL_EXPECT(duration.count() >= 0);
}

void test_evaluate_single_try()
{
    int counter = 0;
    msl::evaluate([&] { ++counter; }, 1);
    MSL_EXPECT(counter == 1);
}

void test_evaluate_counts_tries()
{
    int counter = 0;
    msl::evaluate([&] { ++counter; }, 50);
    MSL_EXPECT(counter == 50);
}

void test_avg_evaluate_returns_nonnegative()
{
    auto duration = msl::avg_evaluate([] { volatile int x = 0; (void)x; }, 10, 5);
    MSL_EXPECT(duration.count() >= 0);
}
} // namespace

void run_bench_tests()
{
    test_evaluate_returns_nonnegative();
    test_evaluate_single_try();
    test_evaluate_counts_tries();
    test_avg_evaluate_returns_nonnegative();
}
