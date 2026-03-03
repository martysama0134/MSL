#include "test_common.h"

#include <limits>

#include <msl/cast.h>

namespace
{
void test_integral_cast_in_range()
{
    const auto val = msl::integral_cast<int>(42.0);
    MSL_EXPECT(val == 42);
}

void test_integral_cast_fractional_throws()
{
    bool thrown = false;
    try
    {
        (void)msl::integral_cast<int>(42.5);
    }
    catch (const msl::truncate_error &)
    {
        thrown = true;
    }
    MSL_EXPECT(thrown);
}

void test_integral_cast_out_of_range_throws()
{
    bool thrown = false;
    try
    {
        (void)msl::integral_cast<short>(1e20);
    }
    catch (const msl::truncate_error &)
    {
        thrown = true;
    }
    MSL_EXPECT(thrown);
}

void test_integral_cast_nan_inf_throw()
{
    bool nan_thrown = false;
    try
    {
        const auto nan = std::numeric_limits<double>::quiet_NaN();
        (void)msl::integral_cast<int>(nan);
    }
    catch (const msl::truncate_error &)
    {
        nan_thrown = true;
    }
    MSL_EXPECT(nan_thrown);

    bool inf_thrown = false;
    try
    {
        const auto inf = std::numeric_limits<double>::infinity();
        (void)msl::integral_cast<int>(inf);
    }
    catch (const msl::truncate_error &)
    {
        inf_thrown = true;
    }
    MSL_EXPECT(inf_thrown);
}

void test_truncate_valid_and_invalid()
{
    const auto ok = msl::truncate<unsigned short>(255.9);
    MSL_EXPECT(ok == 255);

    bool thrown = false;
    try
    {
        (void)msl::truncate<unsigned short>(100000.66);
    }
    catch (const msl::truncate_error &)
    {
        thrown = true;
    }
    MSL_EXPECT(thrown);
}
} // namespace

void run_cast_tests()
{
    test_integral_cast_in_range();
    test_integral_cast_fractional_throws();
    test_integral_cast_out_of_range_throws();
    test_integral_cast_nan_inf_throw();
    test_truncate_valid_and_invalid();
}
