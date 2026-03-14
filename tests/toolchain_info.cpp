#include <format>
#include <iostream>
#include <ranges>
#include <string>
#include <version>

int main()
{
#if defined(_MSC_VER)
    std::cout << "compiler=msvc _MSC_VER=" << _MSC_VER << '\n';
#elif defined(__clang__)
    std::cout << "compiler=clang "
              << __clang_major__ << '.'
              << __clang_minor__ << '.'
              << __clang_patchlevel__ << '\n';
#elif defined(__GNUC__)
    std::cout << "compiler=gcc "
              << __GNUC__ << '.'
              << __GNUC_MINOR__ << '.'
              << __GNUC_PATCHLEVEL__ << '\n';
#else
    std::cout << "compiler=unknown\n";
#endif

#if defined(_LIBCPP_VERSION)
    std::cout << "_LIBCPP_VERSION=" << _LIBCPP_VERSION << '\n';
#endif

#if defined(__GLIBCXX__)
    std::cout << "__GLIBCXX__=" << __GLIBCXX__ << '\n';
#endif

#ifdef __cpp_lib_format
    std::cout << "__cpp_lib_format=" << __cpp_lib_format << '\n';
#else
    std::cout << "__cpp_lib_format=undefined\n";
#endif

#ifdef __cpp_lib_ranges
    std::cout << "__cpp_lib_ranges=" << __cpp_lib_ranges << '\n';
#else
    std::cout << "__cpp_lib_ranges=undefined\n";
#endif

    const auto out = std::format("toolchain probe v{}", 4);
    auto even = std::views::iota(0, 6) | std::views::filter([](int value) {
        return (value % 2) == 0;
    });

    int sum = 0;
    for (int value : even)
        sum += value;

    std::cout << "format_smoke=" << out << '\n';
    std::cout << "ranges_smoke_sum=" << sum << '\n';
    return sum == 6 ? 0 : 1;
}
