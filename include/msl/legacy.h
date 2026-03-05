#ifndef MSL_LEGACY_H__
#define MSL_LEGACY_H__
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2026 martysama0134. All rights reserved.
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
#include <functional>
#include <random>
#include <utility>

namespace msl
{

//! @brief clamp value in [min_value, max_value], auto-swapping bounds when reversed
template <typename T> constexpr T minmax(T min_value, T value, T max_value)
{
	if (max_value < min_value)
		std::swap(min_value, max_value);

	if (value < min_value)
		return min_value;
	if (max_value < value)
		return max_value;
	return value;
}

//! @brief compatibility wrapper similar to deprecated std::bind1st-style usage
template <class F, class... Args>
constexpr decltype(auto) bind1st(F && f, Args &&... args)
{
	return std::bind(std::forward<F>(f), std::forward<Args>(args)..., std::placeholders::_1);
}

//! @brief compatibility wrapper similar to deprecated std::bind2nd-style usage
template <class F, class... Args>
constexpr decltype(auto) bind2nd(F && f, Args &&... args)
{
	return std::bind(std::forward<F>(f), std::placeholders::_1, std::forward<Args>(args)...);
}

//! @brief compatibility wrapper similar to removed std::random_shuffle(first, last)
template <class RandomIt> void random_shuffle(RandomIt first, RandomIt last)
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(first, last, g);
}

//! @brief compatibility wrapper similar to removed std::random_shuffle(first, last, g)
template <class RandomIt, class Generator>
void random_shuffle(RandomIt first, RandomIt last, Generator && g)
{
	std::shuffle(first, last, std::forward<Generator>(g));
}

//! @brief compatibility wrapper similar to removed std::mem_fun for void member functions
template <class Ty> constexpr auto void_mem_fun(void (Ty::*pm)())
{
	return [pm](Ty * p)
	{
		(p->*pm)();
	};
}

//! @brief compatibility wrapper similar to removed std::mem_fun_ref for void member functions
template <class Ty> constexpr auto void_mem_fun_ref(void (Ty::*pm)())
{
	return [pm](Ty & x)
	{
		(x.*pm)();
	};
}

} // namespace msl

#endif // MSL_LEGACY_H__
