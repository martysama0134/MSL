#include "test_common.h"

void run_pool_tests();
void run_file_ptr_tests();
void run_utils_tests();
void run_cast_tests();
void run_legacy_tests();

int main()
{
    const std::vector<msl_test::test_case> tests = {
        {"shared_pool regression tests", run_pool_tests},
        {"file_ptr regression tests", run_file_ptr_tests},
        {"utils regression tests", run_utils_tests},
        {"cast regression tests", run_cast_tests},
        {"legacy compatibility tests", run_legacy_tests},
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
