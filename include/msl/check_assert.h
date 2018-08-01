#pragma once

#include <cstdlib>

namespace msl {
	inline auto check_assert = [](bool condition) {
		if (!(condition))
			std::abort();
	};
}
