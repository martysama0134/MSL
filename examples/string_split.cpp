#include <iostream>
#include <msl/utils.h>

int main()
{
    const auto parts = msl::string_split("alpha::beta::gamma", "::");
    std::cout << "parts=" << parts.size() << '\n';
    for (const auto & part : parts)
        std::cout << part << '\n';
    return 0;
}
