#pragma once

#include <algorithm>
#include <vector>

namespace msl
{
//! @brief range_iterator used for range
template <class T> class range_iterator
{
	T m_value{};

public:
	range_iterator(T value) : m_value{value} {}
	T operator*() { return m_value; }
	range_iterator<T> & operator++()
	{
		++m_value;
		return *this;
	}
	range_iterator<T> & operator--()
	{
		--m_value;
		return *this;
	}
	range_iterator<T> operator++(int)
	{
		++m_value;
		return *this;
	}
	range_iterator<T> operator--(int)
	{
		--m_value;
		return *this;
	}
	bool operator!=(range_iterator<T> & r) { return m_value != *r; }
};

//! @brief range mostly used in for-range (no memory allocation)
template <class T> class range
{
	range_iterator<T> m_min{0};
	range_iterator<T> m_max;

public:
	range(T max) : m_max{max} {}
	range(T min, T max) : m_min{min}, m_max{max} {}
	range_iterator<T> begin()
	{
		if (*m_min == *m_max)
			return m_max;
		return m_min;
	}
	range_iterator<T> end() { return m_max; }
};

using crange = range<char>;
using irange = range<int>;
using llrange = range<long long>;
using frange = range<float>;
using drange = range<double>;

//! @brief xrange mostly used in for-range (it uses std::vector with n=((max-min)/diff) elements)
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
		m_vec.resize(static_cast<size_t>((max - min) / diff));
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
