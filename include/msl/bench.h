#pragma once

#include <chrono>
#include <iostream>
namespace msl
{
template <class F> auto evaluate(F && func, size_t tries = 1)
{
	auto start = std::chrono::steady_clock::now();
	for (auto i = 0; i < tries; i++)
		func();
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
}

class bench
{
public:
	template <class F> bench(F && func, size_t tries = 10000) { std::cout << "Elapsed time: " << evaluate(func, tries).count() << "ms\n"; }
};

} // namespace msl
