#pragma once

#include <algorithm>
#include <vector>

namespace msl
{
/*template <class T> class range
{
	T m_min{};
	T m_max{};
	T * m_ptr{};
	T * m_ptr2{};

public:
	range(T max) : m_max{max} { m_ptr2 += max; }
	//range(T min, T max) : m_min{ min } m_max { max } {}
	T * begin() { return m_ptr++; }
	T * end() { return m_ptr2; }
};*/

template <class T> class xrange
{
	std::vector<T> m_vec;

public:
	xrange(T max) : xrange(0, max) {}
	xrange(T min, T max)
	{
		if (min >= max)
			std::runtime_error("xrange min >= max");
		m_vec.resize(max - min);
		std::generate(m_vec.begin(), m_vec.end(), [n = min]() mutable { return n++; });
	}
	auto begin() { return std::begin(m_vec); }
	auto end() { return std::end(m_vec); }
};
} // namespace msl
