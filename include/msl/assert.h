#ifndef __MSL_CAST_ASSERT_H__
#define __MSL_CAST_ASSERT_H__
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

#include <cstdlib>
#include <string>

namespace msl
{
inline void check_assert(bool condition)
{
	if (!condition)
		std::abort();
}


//! @brief msl::test_error struct
struct test_error : std::exception
{
	std::string testName;
	test_error(const std::string & name) : testName(name) {}
	const char* what() const noexcept override { return testName.c_str(); }
};

inline void test_assert(const std::string & name, bool condition)
{
	if (!condition)
		throw test_error(name);
}
} // namespace msl
#endif
