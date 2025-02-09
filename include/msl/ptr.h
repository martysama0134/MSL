#ifndef MSL_PTR_H__
#define MSL_PTR_H__
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

#include <functional> // For std::hash
#include <memory> // For std::shared_ptr

namespace msl
{

/// @brief A scoped shared pointer that prevents unintended ownership transfer.
/// @tparam T The type of the object being managed.
template <typename T> class scoped_shared_ptr : private std::shared_ptr<T>
{
public:
	/// @brief Constructs a scoped_shared_ptr from a shared_ptr.
	/// @param ptr The shared_ptr to take ownership of.
	scoped_shared_ptr(std::shared_ptr<T> ptr) : std::shared_ptr<T>(std::move(ptr)) {}

	/// @brief Checks whether the stored pointer is null.
	/// @return True if the stored pointer is null, false otherwise.
	bool operator!() const { return !this->get(); }

	/// @brief Provides access to the stored pointer via the arrow operator.
	/// @return The raw pointer.
	T* operator->() const { return this->get(); }

	/// @brief Deleted dereference operator to prevent direct access.
	T* operator*() const = delete;

	/// @brief Provides an explicit conversion to bool.
	/// @return True if the stored pointer is not null, false otherwise.
	explicit operator bool() const { return this->get() != nullptr; }

	/// @brief Deleted implicit conversion to std::shared_ptr to prevent storing in containers.
	operator std::shared_ptr<T>() const = delete;

	/// @brief Deleted copy constructor to ensure scoped ownership.
	scoped_shared_ptr(const scoped_shared_ptr&) = delete;

	/// @brief Deleted copy assignment operator to ensure scoped ownership.
	scoped_shared_ptr& operator=(const scoped_shared_ptr&) = delete;

	/// @brief Deleted move constructor to prevent ownership transfer.
	scoped_shared_ptr(scoped_shared_ptr&&) = delete;

	/// @brief Deleted move assignment operator to prevent ownership transfer.
	scoped_shared_ptr& operator=(scoped_shared_ptr&&) = delete;

	/// @brief Default destructor. Prevents explicit deletion since ownership is controlled.
	~scoped_shared_ptr() = default;
}; // scoped_shared_ptr


/// @brief A non-owning pointer wrapper to prevent accidental ownership semantics.
/// @tparam T The type of the object being pointed to.
template <typename T> class no_owner
{
public:
	/// @brief Constructs a no_owner from a raw pointer.
	/// @param ptr The raw pointer to wrap.
	no_owner(T* ptr) : ptr_(ptr) {}

	/// @brief Checks whether the stored pointer is null.
	/// @return True if the stored pointer is null, false otherwise.
	bool operator!() const { return !ptr_; }

	/// @brief Provides access to the stored pointer via the arrow operator.
	/// @return The raw pointer.
	T* operator->() const { return ptr_; }

	/// @brief Deleted dereference operator to prevent direct access.
	T& operator*() const = delete;

	/// @brief Deleted copy constructor to ensure single non-ownership.
	no_owner(const no_owner&) = delete;

	/// @brief Deleted copy assignment operator to ensure single non-ownership.
	no_owner& operator=(const no_owner&) = delete;

	/// @brief Deleted move constructor to prevent ownership transfer.
	no_owner(no_owner&&) = delete;

	/// @brief Deleted move assignment operator to prevent ownership transfer.
	no_owner& operator=(no_owner&&) = delete;

	/// @brief Allows assignment with a raw pointer.
	/// @param ptr The raw pointer to assign.
	/// @return Reference to this no_owner instance.
	no_owner& operator=(T* ptr)
	{
		ptr_ = ptr;
		return *this;
	}

	/// @brief Default destructor. Prevents explicit deletion since the wrapper does not own the pointer.
	~no_owner() = default;

	/// @brief Provides an explicit conversion to bool.
	/// @return True if the stored pointer is not null, false otherwise.
	explicit operator bool() const { return ptr_ != nullptr; }

	/// @brief Deleted implicit conversion to raw pointer to enforce controlled access.
	operator T* () const = delete;

	/// @brief Implicit conversion to a const-qualified no_owner.
	/// @tparam U The type of the object being pointed to (defaults to T).
	/// @return A no_owner instance with const-qualified type.
	template<typename U = T>
	operator no_owner<const U>() const { return no_owner<const U>(ptr_); }

private:
	T* ptr_{};  ///< The wrapped raw pointer.
}; // no_owner



/// @brief A non-owning observer pointer, similar to std::experimental::observer_ptr.
/// @tparam T The type of the object being observed.
template <typename T> class observer_ptr
{
public:
	/// @brief Constructs an observer_ptr from a raw pointer.
	/// @param ptr The raw pointer to observe.
	constexpr observer_ptr(T * ptr = nullptr) noexcept : ptr_(ptr) {}

	/// @brief Resets the observed pointer.
	/// @param ptr The new raw pointer to observe.
	void reset(T * ptr = nullptr) noexcept { ptr_ = ptr; }

	/// @brief Releases ownership of the observed pointer.
	/// @return The raw pointer that was being observed.
	T * release() noexcept
	{
		T * old_ptr = ptr_;
		ptr_ = nullptr;
		return old_ptr;
	}

	/// @brief Swaps the observed pointer with another observer_ptr.
	/// @param other The other observer_ptr to swap with.
	void swap(observer_ptr & other) noexcept { std::swap(ptr_, other.ptr_); }

	/// @brief Checks whether the stored pointer is null.
	/// @return True if the stored pointer is null, false otherwise.
	constexpr explicit operator bool() const noexcept { return ptr_ != nullptr; }

	/// @brief Provides access to the stored pointer via the arrow operator.
	/// @return The raw pointer.
	constexpr T * operator->() const noexcept { return ptr_; }

	/// @brief Provides access to the stored pointer.
	/// @return The raw pointer.
	constexpr T * get() const noexcept { return ptr_; }

	/// @brief Deleted copy constructor and assignment to enforce explicit handling.
	observer_ptr(const observer_ptr &) = default;
	observer_ptr & operator=(const observer_ptr &) = default;

	/// @brief Default destructor.
	~observer_ptr() = default;

	/// @brief Creates an observer_ptr from a raw pointer.
	/// @param ptr The raw pointer to observe.
	/// @return An observer_ptr wrapping the given pointer.
	static constexpr observer_ptr make_observer(T * ptr) noexcept { return observer_ptr(ptr); }

private:
	T * ptr_; ///< The observed raw pointer.
}; // observer_ptr

} // namespace msl


/// @brief Hash specialization for observer_ptr to allow usage in unordered containers.
namespace std
{
	template <typename T> struct hash<msl::observer_ptr<T>>
	{
		std::size_t operator()(const msl::observer_ptr<T> & op) const noexcept
		{
			return std::hash<T*>{}(op.get());
		}
	};
}

#endif // MSL_PTR_H__
