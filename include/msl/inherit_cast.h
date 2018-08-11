#pragma once
#include <utility>
namespace msl
{
//! @brief more meaningful cast between dynamic_cast and static_cast
template <class T, class U> constexpr T inherit_cast(U && u) noexcept
{
	return static_cast<T>(std::forward<U>(u));
}
} // namespace msl
