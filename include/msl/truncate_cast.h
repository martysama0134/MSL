#pragma once

#include <exception>
#include <cmath>
namespace msl
{
/// \brief msl::truncate_error struct
struct truncate_error : public std::exception
{
	const char * what() const throw() { return "MSL::Truncate Cast Exception"; }
};
/// \brief msl::truncate_cast truncate with no check
template <class T, class U> constexpr T truncate_cast(U u)
{
	return static_cast<T>(std::trunc(u));
}
/// \brief msl::truncate: truncate and throw msl::truncate_error if check fails
template <class T, class U> constexpr T truncate(U u)
{
	T t = truncate_cast<T>(u);
	if (static_cast<U>(t) != std::trunc(u))
		throw truncate_error();
	return t;
}
/// \brief msl::integral_cast: from floating points to integral types only and throw msl::truncate_error if check fails (slight faster than truncate)
template <class T, class U> constexpr T integral_cast(U u)
{
	T t = static_cast<T>(u);
	if (static_cast<U>(t) != std::trunc(u))
		throw truncate_error();
	return t;
}
} // namespace msl
