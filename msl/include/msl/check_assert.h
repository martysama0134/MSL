#pragma once

#include <cstdlib>

namespace msl
{
inline void check_assert(bool condition)
{
	if (!(condition))
		std::abort();
};
} // namespace msl
