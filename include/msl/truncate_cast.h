#pragma once

#include <exception>
#include <cmath>
namespace msl
{
struct truncate_error : public std::exception
{
	const char * what() const throw() { return "MSL::Truncate Cast Exception"; }
};
template <class T, class U> constexpr T truncate_cast(U u)
{
	return static_cast<T>(u);
}
template <class T, class U> constexpr T truncate(U u)
{
	u = std::trunc(u);
	T t = truncate_cast<T>(u);
	if (static_cast<U>(t) != u)
		throw truncate_error();
	return t;
}
} // namespace msl
