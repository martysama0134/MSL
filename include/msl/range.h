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

/// \brief xrange mostly used in for-range (it uses std::vector with n=((max-min)/diff) elements)
template <class T> class xrange
{
	std::vector<T> m_vec;

public:
	xrange(T max) : xrange(0, max, 1) {}
	xrange(T min, T max) : xrange(min, max, 1) {}
	xrange(T min, T max, T diff)
	{
		if (min >= max)
			throw std::runtime_error("xrange min >= max");
		if (diff <= 0)
			throw std::runtime_error("xrange diff <= 0");
		// 4x faster than emplace_back
		m_vec.resize((max - min) / diff);
		for (auto & e : m_vec)
		{
			e += min;
			min += diff;
		}
	}
	auto begin() { return std::begin(m_vec); }
	auto end() { return std::end(m_vec); }
};

using xcrange = xrange<char>;
using xirange = xrange<int>;
using xllrange = xrange<long long>;
using xfrange = xrange<float>;
using xdrange = xrange<double>;
} // namespace msl
