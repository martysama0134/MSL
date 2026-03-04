#include <msl/msl.h>

int header_smoke_no_exceptions()
{
    msl::check_assert(true);
    msl::test_assert("no_exceptions", true);
    MSL_TEST_ASSERT("macro_no_exceptions", true);
    MSL_TEST_ASSERT_WN(true);
    return msl::integral_cast<int>(42.0);
}
