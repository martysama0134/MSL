#include <cstdio>
#include <iostream>
#include <msl/file_ptr.h>
#include <string>

int main()
{
    const std::string path = "msl_example_file_ptr_io.txt";

    {
        msl::file_ptr file(path, "wb");
        if (!file)
        {
            std::cerr << "failed to open file for write\n";
            return 1;
        }
        const auto written = file.string_write("hello");
        std::cout << "written=" << written << '\n';
    }

    {
        msl::file_ptr file(path, "rb");
        if (!file)
        {
            std::cerr << "failed to open file for read\n";
            return 1;
        }
        std::cout << "content=" << file.string_read() << '\n';
    }

    std::remove(path.c_str());
    return 0;
}
