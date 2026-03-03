#include "test_common.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <string_view>
#include <vector>

#include <msl/file_ptr.h>

namespace
{
void remove_file_if_exists(const std::string & path)
{
    std::remove(path.c_str());
}

void write_text_file(const std::string & path, const std::string & contents)
{
    std::FILE * raw = std::fopen(path.c_str(), "wb");
    MSL_EXPECT(raw != nullptr);
    const auto written = std::fwrite(contents.data(), 1, contents.size(), raw);
    MSL_EXPECT(written == contents.size());
    std::fclose(raw);
}

void test_open_with_non_null_terminated_string_view()
{
    const std::string path = "msl_file_ptr_non_null_terminated.tmp";
    remove_file_if_exists(path);
    write_text_file(path, "abc");

    std::vector<char> raw_path(path.begin(), path.end());
    std::string_view view(raw_path.data(), raw_path.size());

    msl::file_ptr file;
    file.open(view, "rb");

    MSL_EXPECT(file.is_open());
    MSL_EXPECT(file.string_read() == "abc");

    remove_file_if_exists(path);
}

void test_reopen_is_safe()
{
    const std::string path_a = "msl_file_ptr_reopen_a.tmp";
    const std::string path_b = "msl_file_ptr_reopen_b.tmp";
    remove_file_if_exists(path_a);
    remove_file_if_exists(path_b);

    write_text_file(path_a, "A");
    write_text_file(path_b, "BC");

    msl::file_ptr file(path_a, "rb");
    MSL_EXPECT(file.is_open());

    file.open(path_b, "rb");
    MSL_EXPECT(file.is_open());
    MSL_EXPECT(file.string_read() == "BC");

    remove_file_if_exists(path_a);
    remove_file_if_exists(path_b);
}

void test_write_reports_bytes()
{
    const std::string path = "msl_file_ptr_write_counts.tmp";
    remove_file_if_exists(path);

    {
        msl::file_ptr file(path, "wb");
        MSL_EXPECT(file.is_open());

        const std::vector<char> bytes_vec = {'a', 'b', 'c'};
        const char raw_bytes[] = {'d', 'e'};

        const auto n1 = file.write(bytes_vec);
        const auto n2 = file.write(static_cast<const void*>(raw_bytes), sizeof(raw_bytes));
        const auto n3 = file.string_write("fg");

        MSL_EXPECT(n1 == bytes_vec.size());
        MSL_EXPECT(n2 == sizeof(raw_bytes));
        MSL_EXPECT(n3 == 2);
    }

    {
        msl::file_ptr file(path, "rb");
        MSL_EXPECT(file.read().size() == 7);
    }

    remove_file_if_exists(path);
}

void test_read_returns_actual_bytes()
{
    const std::string path = "msl_file_ptr_read_size.tmp";
    remove_file_if_exists(path);
    write_text_file(path, "123");

    msl::file_ptr file(path, "rb");
    const auto data = file.read(10);
    MSL_EXPECT(data.size() == 3);

    remove_file_if_exists(path);
}

void test_string_read_buffer_behavior()
{
    const std::string path = "msl_file_ptr_string_read.tmp";
    remove_file_if_exists(path);
    write_text_file(path, "hello");

    msl::file_ptr file(path, "rb");

    char short_buf[3] = {};
    file.string_read(short_buf, sizeof(short_buf));
    MSL_EXPECT(std::strcmp(short_buf, "he") == 0);

    file.seek(0);
    char untouched[4] = {'x', 'y', 'z', '\0'};
    file.string_read(untouched, 0);
    MSL_EXPECT(std::strcmp(untouched, "xyz") == 0);

    remove_file_if_exists(path);
}
} // namespace

void run_file_ptr_tests()
{
    test_open_with_non_null_terminated_string_view();
    test_reopen_is_safe();
    test_write_reports_bytes();
    test_read_returns_actual_bytes();
    test_string_read_buffer_behavior();
}
