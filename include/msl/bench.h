#ifndef MSL_BENCH_H__
#define MSL_BENCH_H__
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2018 martysama0134. All rights reserved.
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

#include <chrono>
#include <iostream>

namespace msl
{

template <class F> auto evaluate(F && func, const std::size_t tries = 100000)
{
	const auto start = std::chrono::steady_clock::now();
	for (std::size_t i = 0; i < tries; i++)
		func();
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
}

template <class F> void bench(F && func, const std::size_t tries = 100000)
{
	std::cout << "Elapsed time: " << evaluate(func, tries).count() << "ms\n";
}

template <class F> void named_bench(const std::string& name, F&& func, const std::size_t tries = 100000)
{
	std::cout << "Bench name: " << name << ", ";
	bench(func, tries);
}

template <class F> auto avg_evaluate(F && func, const std::size_t tries = 10000, const std::size_t retries = 100)
{
    auto val = evaluate(func, tries * retries);
    return val / retries;
}

template <class F> void avg_bench(F && func, const std::size_t tries = 10000, const std::size_t retries = 100)
{
    std::cout << "Elapsed avg time: " << avg_evaluate(func, tries, retries).count() << "ms\n";
}

template <class F> void avg_named_bench(const std::string& name, F&& func, const std::size_t tries = 10000, const std::size_t retries = 100)
{
	std::cout << "Avg bench name: " << name << ", ";
	avg_bench(func, tries, retries);
}

} // namespace msl
#endif // MSL_BENCH_H__
