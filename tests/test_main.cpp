#include "test_common.h"

void run_pool_tests();
void run_file_ptr_tests();
void run_utils_tests();
void run_range_tests();
void run_feature_gate_tests();
void run_cast_tests();
void run_legacy_tests();
void run_traits_tests();
void run_ptr_tests();
void run_random_tests();
void run_bench_tests();

int main()
{
    const std::vector<msl_test::test_case> tests = {
        {"shared_pool regression tests", run_pool_tests},
        {"file_ptr regression tests", run_file_ptr_tests},
        {"utils regression tests", run_utils_tests},
        {"range regression tests", run_range_tests},
        {"feature gate regression tests", run_feature_gate_tests},
        {"traits regression tests", run_traits_tests},
        {"cast regression tests", run_cast_tests},
        {"legacy compatibility tests", run_legacy_tests},
        {"ptr regression tests", run_ptr_tests},
        {"random regression tests", run_random_tests},
        {"bench regression tests", run_bench_tests},
    };

    const int failures = msl_test::run_all(tests);
    if (failures != 0)
    {
        std::cerr << failures << " test suite(s) failed\n";
        return 1;
    }

    std::cout << "All deterministic tests passed.\n";
    return 0;
}
