#pragma once

#include <chrono>
#include <functional>
#include <iostream>
namespace msl
{
class bench
{
public:
	template <class F, class... Args> bench(F && func, Args &&... args, size_t tries = 10000)
	{
		std::cout << "Elapsed time: " << evaluate(func, args..., tries).count() << "ms\n";
	}
};

template <class F, class... Args> auto evaluate(F && func, Args &&... args, size_t tries = 1)
{
	auto start = std::chrono::steady_clock::now();
	for (auto i = 0; i < tries; i++)
		std::invoke(std::forward<decltype(func)>(func), std::forward<Args>(args)...);
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
}
} // namespace msl
