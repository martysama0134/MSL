#ifndef __MSL_SCOPED_SHARED_PTR_H__
#define __MSL_SCOPED_SHARED_PTR_H__
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2025 martysama0134. All rights reserved.
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
#include <memory>

template <typename T> class scoped_shared_ptr : private std::shared_ptr<T>
{
public:
	explicit scoped_shared_ptr(std::shared_ptr<T> ptr) : std::shared_ptr<T>(std::move(ptr)) {} // Correctly initialize base class

	// Allow access only through arrow operator
	T * operator->() const { return this->get(); }

	// Delete dereference operator
	T * operator*() const = delete;

	// Prevent storing in containers by deleting implicit conversion to std::shared_ptr
	operator std::shared_ptr<T>() const = delete;

	// Delete copy/move constructors and assignment
	scoped_shared_ptr(const scoped_shared_ptr &) = delete;
	scoped_shared_ptr & operator=(const scoped_shared_ptr &) = delete;
	scoped_shared_ptr(scoped_shared_ptr &&) = delete;
	scoped_shared_ptr & operator=(scoped_shared_ptr &&) = delete;

	// Prevent explicit deletion
	~scoped_shared_ptr() = default;
};
#endif // __MSL_SCOPED_SHARED_PTR_H__
