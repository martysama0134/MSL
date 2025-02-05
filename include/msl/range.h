#ifndef __MSL_RANGE_H__
#define __MSL_RANGE_H__
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

#include <algorithm>
#include <vector>

namespace msl
{
//! @brief range_iterator used for range
template <class T> class range_iterator
{
	T m_value_{};

public:
	explicit range_iterator(const T value) : m_value_{value} {}
	constexpr T operator*() const noexcept { return m_value_; }
	constexpr range_iterator<T> & operator++() noexcept
	{
		++m_value_;
		return *this;
	}
	constexpr range_iterator<T> & operator--() noexcept
	{
		--m_value_;
		return *this;
	}
	constexpr range_iterator<T> operator++(int) noexcept
	{
		++m_value_;
		return *this;
	}
	constexpr range_iterator<T> operator--(int) noexcept
	{
		--m_value_;
		return *this;
	}
	constexpr bool operator!=(const range_iterator<T> & r) const noexcept { return m_value_ != *r; }
};

//! @brief range mostly used in for-range (no memory allocation)
template <class T> class range
{
	range_iterator<T> m_min_{0};
	range_iterator<T> m_max_;

public:
	explicit constexpr range(T max) noexcept : m_min_{0}, m_max_{max} {}
	constexpr range(const T min, const T max) noexcept : m_min_{min}, m_max_{max} {}

	[[nodiscard]] constexpr range_iterator<T> begin() const noexcept { return *m_min_ >= *m_max_ ? m_max_ : m_min_; }
	[[nodiscard]] constexpr range_iterator<T> end() const noexcept { return m_max_; }
};

// Type aliases
using crange = range<char>;
using irange = range<int>;
using llrange = range<long long>;
using frange = range<float>;
using drange = range<double>;

//! @brief xrange mostly used in for-range (it uses std::vector with n=((max-min)/diff) elements)
template <class T> class xrange
{
	std::vector<T> m_vec_;

public:
	explicit xrange(const T max) : xrange(0, max, 1) {}
	xrange(const T min, const T max) : xrange(min, max, 1) {}
	xrange(const T min, const T max, const T diff) { init(min, max, diff); };
	[[nodiscard]] auto begin() const noexcept { return std::begin(m_vec_); }
	[[nodiscard]] auto end() const noexcept { return std::end(m_vec_); }

private:
	void init(T min, const T max, const T diff)
	{
		if (min >= max || diff <= 0)
			return;

		// 4x faster than emplace_back
		if constexpr (std::floating_point<T>)
			m_vec_.resize(static_cast<std::size_t>((max - min) / diff));
		else
			m_vec_.resize(static_cast<std::size_t>((max - min) / diff) + ((max - min) % diff ? 1 : 0));

		std::generate(m_vec_.begin(), m_vec_.end(),
					  [&min, diff]()
					  {
						  T current = min;
						  min += diff;
						  return current;
					  });
	}
};

// Type aliases for xrange
using xcrange = xrange<char>;
using xirange = xrange<int>;
using xllrange = xrange<long long>;
using xfrange = xrange<float>;
using xdrange = xrange<double>;


// for_each_indexed (iterator-based)
template <typename It, typename Func> void for_each_indexed(It begin, It end, Func func)
{
	std::size_t index = 0;
	for (auto it = begin; it != end; ++it, ++index)
	{
		func(index, *it);
	}
}

// for_each_indexed (container-based)
template <typename Container, typename Func> void for_each_indexed(Container & c, Func func)
{
	for_each_indexed(std::begin(c), std::end(c), func);
}


} // namespace msl
#endif
