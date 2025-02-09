#ifndef __MSL_POOL_H__
#define __MSL_POOL_H__
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
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_set>
#include <vector>

namespace msl
{

template <typename T> class shared_pool : public std::enable_shared_from_this<shared_pool<T>>
{
public:
	using PoolType = std::shared_ptr<shared_pool<T>>;
	using ObjectType = std::shared_ptr<T>;
    using Initializer = std::function<void(ObjectType&)>;
    using Destroyer = std::function<void(ObjectType&)>;

	static inline const Initializer default_initializer = [](ObjectType &) {};
	static inline const Destroyer default_destroyer = [](ObjectType &) {};

	class handle
	{
	protected:
		explicit handle(std::weak_ptr<shared_pool<T>> pool, std::shared_ptr<T> object, Destroyer destroyer)
			: pool_(pool), object_(object), destroyer_(destroyer)
		{
			if (pool_.expired())
			{
				if (object_) // clean up
					destroyer_(object_);
				throw std::invalid_argument("shared_pool::handle pool can't be nullptr");
			}
		}
		friend shared_pool<T>;

	public:
		~handle()
		{
			if (pool_.expired())
			{
				if (object_) // clean up
					destroyer_(object_);
				return;
			}
			if (object_)
				pool_.lock()->release(object_);
		}

		// copy deleted
		handle(const handle &) = delete;
		handle & operator=(const handle &) = delete;

		// move declared
		handle(handle && other) noexcept : pool_(other.pool_), object_(other.object_) { other.object_.reset(); }
		handle & operator=(handle && other) noexcept
		{
			if (this != &other)
			{
				// release old handle if set
				if (object_)
				{
					if (pool_.expired())
						destroyer_(object_);
					else
						pool_.lock()->release(object_);
					object_.reset();
				}
				// move (even if it's from different pool)
				pool_ = std::move(other.pool_);
				object_ = std::move(other.object_);
				destroyer_ = std::move(other.destroyer_);
				other.object_.reset();
			}
			return *this;
		}

		constexpr T * operator->() { return object_.get(); }
		constexpr T & operator*() { return *(object_.get()); }
		constexpr explicit operator bool() const { return object_ != nullptr; }
		constexpr T * get() const noexcept { return object_; }

	private:
		std::weak_ptr<shared_pool<T>> pool_;
		std::shared_ptr<T> object_;
		Destroyer destroyer_;
	}; // handle

	// Delete copy constructor and copy assignment
	shared_pool(const shared_pool &) = delete;
	shared_pool & operator=(const shared_pool &) = delete;

	// Delete move constructor and move assignment
	shared_pool(shared_pool &&) = delete;
	shared_pool & operator=(shared_pool &&) = delete;

	[[nodiscard]] handle acquire()
	{
		std::lock_guard<std::mutex> lock(mutex_);
		if (available_.empty())
			return handle(this->weak_from_this(), allocate(true), destroyer_);

		auto obj = available_.back();
		initializer_(obj); // before pop in case of std exception
		available_.pop_back(); // remove from available_ but keep from allocated
		return handle(this->weak_from_this(), obj, destroyer_);
	}

	std::size_t available() const
	{
		std::lock_guard<std::mutex> lock(mutex_);
		return available_.size();
	}

	std::size_t size() const
	{
		std::lock_guard<std::mutex> lock(mutex_);
		return allocated_.size();
	}

	std::size_t capacity() const
	{
		std::lock_guard<std::mutex> lock(mutex_);
		return allocated_.capacity();
	}

	void reserve(std::size_t n)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		const auto total = allocated_.size();
		if (n <= total)
			return;

		const auto left = n - total;
		available_.reserve(available_.size() + left);
		allocated_.reserve(available_.size() + left);
	}

	void prepare(std::size_t n)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		const auto total = allocated_.size();
		if (n <= total)
			return;

		const auto left = n - total;
		available_.reserve(available_.size() + left);
		allocated_.reserve(available_.size() + left);
		for (std::size_t i = 0; i < left; ++i)
			available_.emplace_back(allocate());
	}
	
	template <typename... Args>
	static PoolType create(Args &&... args)
	{
		return std::shared_ptr<shared_pool<T>>(new shared_pool<T>(std::forward<Args>(args)...)); //make_shared can't be added in friend
	}

	template <typename... Args>
	static PoolType create_with_methods(Initializer initializer = default_initializer, Destroyer destroyer = default_destroyer,
										Args &&... args)
	{
		auto obj = std::shared_ptr<shared_pool<T>>(new shared_pool<T>(std::forward<Args>(args)...)); //make_shared can't be added in friend
		obj->set_methods(initializer, destroyer);
		return obj;
	}

	void set_methods(Initializer initializer = default_initializer, Destroyer destroyer = default_destroyer)
	{
		initializer_ = initializer;
		destroyer_ = destroyer;
	}

protected:
	template <typename... Args>
	shared_pool(Args &&... args)
	{
		creator_ = [tuple = std::make_tuple(std::forward<Args>(args)...)]()
		{
			return std::apply([](auto &&... params) {
				return std::make_shared<T>(std::forward<decltype(params)>(params)...);
			}, tuple);
		};
	}

	void release(ObjectType object_)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		destroyer_(object_);
		available_.emplace_back(object_);
	}

	[[nodiscard]] ObjectType allocate(bool init = false)
	{
		auto obj = creator_();
		if (init)
			initializer_(obj); // before emplace in case of std exception
		return allocated_.emplace_back(obj);
	}

private:
	std::vector<ObjectType> allocated_; // pick unordered_set only if search will be implementated later on
	std::vector<ObjectType> available_; // reserve+pop_back
	Initializer initializer_ = default_initializer; // used to initialize the obj when acquired
	Destroyer destroyer_ = default_destroyer; // used to destroy the obj when expired
	std::function<ObjectType()> creator_; // used to create the object instance with variadic arguments
	mutable std::mutex mutex_;
}; // shared_pool

} // namespace msl

#endif // __MSL_POOL_H__
