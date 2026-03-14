#pragma once

#include <functional>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace msl_test
{

struct test_case
{
    const char * name;
    std::function<void()> fn;
};

inline void expect(bool condition, const char * expr, const char * file, int line)
{
    if (condition)
        return;

    throw std::runtime_error(std::format("{}:{} expectation failed: {}", file, line, expr));
}

inline int run_all(const std::vector<test_case> & cases)
{
    int failed = 0;
    for (const auto & tc : cases)
    {
        try
        {
            tc.fn();
            std::cout << "[PASS] " << tc.name << '\n';
        }
        catch (const std::exception & ex)
        {
            ++failed;
            std::cerr << "[FAIL] " << tc.name << ": " << ex.what() << '\n';
        }
        catch (...)
        {
            ++failed;
            std::cerr << "[FAIL] " << tc.name << ": unknown exception\n";
        }
    }
    return failed;
}

} // namespace msl_test

#define MSL_EXPECT(expr) ::msl_test::expect((expr), #expr, __FILE__, __LINE__)
