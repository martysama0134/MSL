#ifndef __MSL_PTR_H__
#define __MSL_PTR_H__
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
};


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
};



/// @brief A non-owning observer pointer.
/// 
/// The observer_ptr class encapsulates a raw pointer without taking ownership.
/// It provides controlled access to the pointer while preventing implicit conversions
/// and direct dereferencing.
/// 
/// @tparam T The type of the object being observed.
template <typename T>
class observer_ptr
{
public:
    /// @brief Constructs an observer_ptr from a raw pointer.
    /// @param ptr A raw pointer to the object to observe.
    observer_ptr(T* ptr) : ptr_(ptr) {}

    /// @brief Default copy constructor.
    observer_ptr(const observer_ptr&) = default;

    /// @brief Default copy assignment operator.
    /// @return A reference to this observer_ptr.
    observer_ptr& operator=(const observer_ptr&) = default;

    /// @brief Logical negation operator.
    /// @return true if the underlying pointer is null, false otherwise.
    bool operator!() const { return !ptr_; }

    /// @brief Arrow operator for member access.
    ///
    /// Provides access to the members of the observed object.
    /// @return The underlying raw pointer.
    T* operator->() const { return ptr_; }

    /// @brief Deleted dereference operator.
    ///
    /// Prevents direct dereferencing of the pointer.
    T& operator*() const = delete;

    /// @brief Deleted move constructor.
    observer_ptr(observer_ptr&&) = delete;

    /// @brief Deleted move assignment operator.
    observer_ptr& operator=(observer_ptr&&) = delete;

    /// @brief Assigns a raw pointer to the observer_ptr.
    /// @param ptr A raw pointer to assign.
    /// @return A reference to this observer_ptr.
    observer_ptr& operator=(T* ptr)
    {
        ptr_ = ptr;
        return *this;
    }

    /// @brief Gets the underlying raw pointer.
    ///
    /// This function provides explicit access to the underlying pointer.
    /// @return The raw pointer.
    T* get() const { return ptr_; }

    /// @brief Destructor.
    ///
    /// The destructor is defaulted since this class does not manage the pointer's lifetime.
    ~observer_ptr() = default;

    /// @brief Explicit conversion to bool.
    /// @return true if the underlying pointer is not null, false otherwise.
    explicit operator bool() const { return ptr_ != nullptr; }

    /// @brief Deleted implicit conversion to raw pointer.
    operator T* () const = delete;

    /// @brief Conversion operator to an observer_ptr of a const type.
    /// @tparam U The type to convert to (defaults to T).
    /// @return An observer_ptr<const U> observing the same raw pointer.
    template<typename U = T>
    operator observer_ptr<const U>() const { return observer_ptr<const U>(ptr_); }

private:
    T* ptr_{};  ///< The wrapped raw pointer.
};


} // namespace msl
#endif // __MSL_PTR_H__
