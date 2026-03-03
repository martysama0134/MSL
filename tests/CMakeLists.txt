add_executable(
    msl_tests
    test_main.cpp
    test_pool.cpp
    test_file_ptr.cpp
    test_utils.cpp
    test_cast.cpp
)

target_link_libraries(msl_tests PRIVATE msl::msl)
target_compile_features(msl_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(msl_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(msl_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME msl.tests COMMAND msl_tests)

add_library(
    msl_header_smoke OBJECT
    headers/assert.cpp
    headers/bench.cpp
    headers/cast.cpp
    headers/file_ptr.cpp
    headers/macro.cpp
    headers/msl.cpp
    headers/pool.cpp
    headers/ptr.cpp
    headers/random.cpp
    headers/range.cpp
    headers/util.cpp
    headers/utils.cpp
)

target_link_libraries(msl_header_smoke PRIVATE msl::msl)
target_compile_features(msl_header_smoke PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(msl_header_smoke PRIVATE /W4 /permissive-)
else()
    target_compile_options(msl_header_smoke PRIVATE -Wall -Wextra -Wpedantic)
endif()
