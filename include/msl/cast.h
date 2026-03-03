#ifndef MSL_CAST_H__
#define MSL_CAST_H__
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2018 martysama0134. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cmath>
#include <exception>
#include <limits>
#include <type_traits>
#include <utility>

namespace msl
{

//! @brief msl::truncate_error struct
struct truncate_error : std::exception
{
	const char * what() const noexcept override { return "MSL::Truncate Cast Exception"; }
};

namespace details
{
template <class T, class U> constexpr T checked_float_to_integral(U u, bool require_exact)
{
	const long double value = static_cast<long double>(u);
	const auto inf = std::numeric_limits<long double>::infinity();
	if (value != value || value == inf || value == -inf)
		throw truncate_error();

	const long double truncated = std::trunc(value);
	if (require_exact && truncated != value)
		throw truncate_error();

	const long double min_v = static_cast<long double>((std::numeric_limits<T>::min)());
	const long double max_v = static_cast<long double>((std::numeric_limits<T>::max)());
	if (truncated < min_v || truncated > max_v)
		throw truncate_error();

	return static_cast<T>(truncated);
}
} // namespace details

//! @brief msl::truncate_cast truncate with no check
template <class T, class U> constexpr T truncate_cast(U u)
{
	return static_cast<T>(std::trunc(u));
}

//! @brief msl::truncate: truncate and throw msl::truncate_error if check fails
template <class T, class U> constexpr T truncate(U u)
{
	if constexpr (std::is_integral_v<T> && std::is_floating_point_v<U>)
		return details::checked_float_to_integral<T>(u, false);

	auto t = truncate_cast<T>(u);
	if (static_cast<U>(t) != std::trunc(u))
		throw truncate_error();
	return t;
}

//! @brief msl::integral_cast: from floating points to integral types only and throw msl::truncate_error if check fails (slight faster than truncate)
template <class T, class U> constexpr T integral_cast(U u)
{
	if constexpr (std::is_integral_v<T> && std::is_floating_point_v<U>)
		return details::checked_float_to_integral<T>(u, true);

	auto t = static_cast<T>(u);
	if (static_cast<U>(t) != std::trunc(u))
		throw truncate_error();
	return t;
}

//! @brief more meaningful cast between dynamic_cast and static_cast
template <class T, class U> constexpr T inherit_cast(U && u) noexcept
{
	return static_cast<T>(std::forward<U>(u));
}

} // namespace msl
#endif // MSL_CAST_H__
