#ifndef __MSL_MACRO_H__
#define __MSL_MACRO_H__
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
#include <iostream>
// clang-format on

//! @brief MSL_FORCE_NOMINMAX is a workaround for Windows' min max macro
//#define MSL_FORCE_NOMINMAX
#ifdef MSL_FORCE_NOMINMAX
	#if defined(min)
		#undef min
	#endif
	#if defined(max)
		#undef max
	#endif
#endif

//! @brief MSL_FOR_LOOP wrapper for the common for incremental loop
#define MSL_FOR_LOOP(count) for (decltype(count) i = 0; i < (count); ++i)
#define MSL_FOR_LOOP_VAR(count, varname) for (decltype(count) varname = 0; varname < (count); varname++)
#define MSL_FOR_LOOP_VAR_START(count, varname, start) for (decltype(count) varname = start; varname < (count); varname++)

//! @brief MSL_RUN_TEST runs the whole test case by passing a function / lambda
#define MSL_RUN_TEST(fnc) \
	try {\
		{(fnc)();}\
		std::cout << "All tests passed." << '\n';\
	}\
	catch (msl::test_error& e) {\
		std::cout << e.what() << " test failed." << '\n';\
	}

//! @brief MSL_TEST_ASSERT check and print condition
#define MSL_TEST_ASSERT(name, condition) \
	if (!(condition)) \
		throw msl::test_error((std::string("Test Assert: ") + (name) + " Condition: " + #condition));

//! @brief MSL_TEST_ASSERT_WN check and print condition without name
#define MSL_TEST_ASSERT_WN(condition) \
	if (!(condition)) \
		throw msl::test_error((std::string("Test Condition: ") + #condition).c_str());

// clang-format off
#endif
