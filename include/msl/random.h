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

#include <random>

namespace msl
{
	template <class T> class random_number
	{
	public:
		explicit random_number(T max) : random_number(0, max) {}
		random_number(T min, T max) : m_dist(min, max)
		{
		}

		T operator()()
		{
			return m_dist(m_rd);
		}
	private:
		std::random_device m_rd;
		std::uniform_int_distribution<T> m_dist;
	};

	using random_int = random_number<int>;
} // namespace msl
#endif
