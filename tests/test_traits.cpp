#include "test_common.h"

#include <array>
#include <span>
#include <string>
#include <vector>

#include <msl/traits.h>

namespace
{

enum class write_route
{
    raw,
    contiguous
};

template <typename T, std::enable_if_t<msl::traits::is_raw_v<T>, int> = 0>
constexpr write_route select_write_route(const T &)
{
    return write_route::raw;
}

template <typename C, std::enable_if_t<msl::traits::is_contiguous_v<C>, int> = 0>
constexpr write_route select_write_route(const C &)
{
    return write_route::contiguous;
}

struct pod_value
{
    int id;
    long long score;
};

static_assert(msl::traits::is_contiguous_v<std::vector<int>>);
static_assert(msl::traits::is_contiguous_v<std::string>);
static_assert(msl::traits::is_contiguous_v<std::array<int, 4>>);
static_assert(!msl::traits::is_contiguous_v<std::vector<bool>>);
static_assert(msl::traits::is_raw_v<int>);
static_assert(!msl::traits::is_raw_v<int *>);
static_assert(!msl::traits::is_raw_v<std::vector<int>>);

void test_write_route_selection()
{
    pod_value pod{7, 42};
    std::vector<int> values = {1, 2, 3};
    std::string text = "abc";
    std::array<int, 4> array_values = {1, 2, 3, 4};
    std::span<int> span_values(array_values);

    MSL_EXPECT(select_write_route(pod) == write_route::raw);
    MSL_EXPECT(select_write_route(values) == write_route::contiguous);
    MSL_EXPECT(select_write_route(text) == write_route::contiguous);
    MSL_EXPECT(select_write_route(array_values) == write_route::contiguous);
    MSL_EXPECT(select_write_route(span_values) == write_route::contiguous);
}

void test_raw_and_contiguous_trait_values()
{
    using small_array = std::array<int, 2>;

    MSL_EXPECT(msl::traits::is_raw_v<pod_value>);
    MSL_EXPECT(!msl::traits::is_raw_v<small_array>);
    MSL_EXPECT(!msl::traits::is_raw_v<std::string>);
}

} // namespace

void run_traits_tests()
{
    test_write_route_selection();
    test_raw_and_contiguous_trait_values();
}
