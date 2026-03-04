#ifndef MSL_CONFIG_H__
#define MSL_CONFIG_H__
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

#include <cstdlib>

#ifndef MSL_HAS_EXCEPTIONS
	#if defined(_CPPUNWIND) || defined(__cpp_exceptions) || defined(__EXCEPTIONS)
		#define MSL_HAS_EXCEPTIONS 1
	#else
		#define MSL_HAS_EXCEPTIONS 0
	#endif
#endif

namespace msl
{
namespace details
{
[[noreturn]] inline void abort_no_exceptions() noexcept
{
	std::abort();
}
} // namespace details
} // namespace msl

#if MSL_HAS_EXCEPTIONS
	#define MSL_THROW(exception_expr) throw(exception_expr)
#else
	// Keep throw sites compilable in -fno-exceptions builds and fail-fast at runtime.
	#define MSL_THROW(exception_expr) \
		do \
		{ \
			::msl::details::abort_no_exceptions(); \
		} while (false)
#endif

#endif // MSL_CONFIG_H__
