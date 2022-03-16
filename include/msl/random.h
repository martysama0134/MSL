#ifndef __MSL_RANDOM_H__
#define __MSL_RANDOM_H__
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2022 martysama0134. All rights reserved.
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

#include <cstdint>
#include <chrono>
#include <random>
#include <type_traits>

namespace msl
{
	//! @brief gen_random_number(min, max)
	template <class T> class gen_random_number
	{
	private:
		template <typename U, typename V = void> struct distribution_deduce;
		template <typename U> struct distribution_deduce<U, typename std::enable_if_t<std::is_integral_v<U>>>
		{
			using dist_type = std::uniform_int_distribution<U>;
		};
		template <typename U> struct distribution_deduce<U, typename std::enable_if_t<std::is_floating_point_v<U>>>
		{
			using dist_type = std::uniform_real_distribution<U>;
		};

	public:
		explicit gen_random_number(T max) : gen_random_number(0, max) {}
		gen_random_number(T min, T max) : m_dist(min, max) {
			set_seed(static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()));
		}
		void set_seed(unsigned int seed) {
			m_re.seed(seed);
		}

		T operator()() { return m_dist(m_re); }

	private:
		std::default_random_engine m_re;
		typename distribution_deduce<T>::dist_type m_dist;
	};
	using gen_random_int = gen_random_number<int>;
	using gen_random_real = gen_random_number<double>;

	//! @brief random_int(min, max)
	template<typename T> std::enable_if_t<std::is_integral_v<T>, T>
	random_int(T min, T max)
	{
		thread_local bool init = false;
		thread_local std::default_random_engine re;
		if (!init)
		{
			init = true;
			re.seed(static_cast<uint32_t>(time(nullptr)));
		}
		std::uniform_int_distribution<T> d(min, max);
		return d(re);
	}

	//! @brief random_real(min, max)
	template<typename T> std::enable_if_t<std::is_floating_point_v<T>, T>
	random_real(T min, T max)
	{
		thread_local bool init = false;
		thread_local std::default_random_engine re;
		if (!init)
		{
			init = true;
			re.seed(static_cast<uint32_t>(time(nullptr)));
		}
		std::uniform_real_distribution<T> d(min, max);
		return d(re);
	}
} // namespace msl

#endif
