#pragma once

#include <chrono>
#include <iostream>
namespace msl
{
template <class F, class... Args> auto evaluate(size_t tries, F && func)
{
	auto start = std::chrono::steady_clock::now();
	for (auto i = 0; i < tries; i++)
		func();
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
}

class bench
{
public:
	template <class F, class... Args> bench(F && func)
	{
		constexpr auto tries = 10000;
		std::cout << "Elapsed time: " << evaluate(tries, func).count() << "ms\n";
	}
};

} // namespace msl
