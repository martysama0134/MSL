#include <iostream>
#include <msl/cast.h>

int main()
{
    try
    {
        const auto value = msl::integral_cast<int>(42.0);
        std::cout << "value=" << value << '\n';
        (void)msl::integral_cast<int>(42.5);
    }
    catch (const msl::truncate_error & ex)
    {
        std::cout << "cast failed: " << ex.what() << '\n';
    }
    return 0;
}
