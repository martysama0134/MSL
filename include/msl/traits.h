#ifndef MSL_TRAITS_H__
#define MSL_TRAITS_H__
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

#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

namespace msl
{
namespace traits
{

template <typename T, typename = void>
struct is_contiguous : std::false_type
{
};

template <typename T>
struct is_contiguous<T, std::void_t<decltype(std::data(std::declval<T &>())), decltype(std::size(std::declval<T &>()))>>
	: std::bool_constant<std::is_pointer_v<decltype(std::data(std::declval<T &>()))>>
{
};

template <typename Alloc>
struct is_contiguous<std::vector<bool, Alloc>, void> : std::false_type
{
};

template <typename T>
inline constexpr bool is_contiguous_v = is_contiguous<std::remove_cvref_t<T>>::value;

template <typename T>
inline constexpr bool is_raw_v =
	std::is_trivially_copyable_v<std::remove_cvref_t<T>> &&
	!std::is_pointer_v<std::remove_cvref_t<T>> &&
	!is_contiguous_v<std::remove_cvref_t<T>>;

} // namespace traits
} // namespace msl

#endif // MSL_TRAITS_H__
