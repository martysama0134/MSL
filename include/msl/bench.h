#pragma once

#include <chrono>
#include <functional>
#include <iostream>
namespace msl
{
template <typename F, typename... Args> inline void bench(F && func, Args &&... args)
{
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();

	std::cout << "Elapsed time: " << duration(func, args...).count() << "ms\n";
}

template <typename F, typename... Args> inline auto duration(F && func, Args &&... args)
{
	auto start = std::chrono::steady_clock::now();
	for (auto i = 0; i < 10000; i++)
		std::invoke(std::forward<decltype(func)>(func), std::forward<Args>(args)...);
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
}
} // namespace msl
