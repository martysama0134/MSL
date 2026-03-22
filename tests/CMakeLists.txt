add_executable(
    msl_tests
    test_main.cpp
    test_pool.cpp
    test_file_ptr.cpp
    test_utils.cpp
    test_range.cpp
    test_feature_gates.cpp
    test_traits.cpp
    test_cast.cpp
    test_legacy.cpp
    test_ptr.cpp
    test_random.cpp
    test_bench.cpp
)

target_link_libraries(msl_tests PRIVATE msl::msl)
target_compile_features(msl_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(msl_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(msl_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME msl.tests COMMAND msl_tests)

add_executable(
    msl_toolchain_info
    toolchain_info.cpp
)

target_link_libraries(msl_toolchain_info PRIVATE msl::msl)
target_compile_features(msl_toolchain_info PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(msl_toolchain_info PRIVATE /W4 /permissive-)
else()
    target_compile_options(msl_toolchain_info PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME msl.toolchain_info COMMAND msl_toolchain_info)

add_library(
    msl_header_smoke OBJECT
    headers/assert.cpp
    headers/bench.cpp
    headers/cast.cpp
    headers/config.cpp
    headers/file_ptr.cpp
    headers/legacy.cpp
    headers/macro.cpp
    headers/msl.cpp
    headers/pool.cpp
    headers/ptr.cpp
    headers/random.cpp
    headers/range.cpp
    headers/traits.cpp
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

if(NOT MSVC)
    add_library(
        msl_header_smoke_no_exceptions OBJECT
        headers/no_exceptions.cpp
    )

    target_link_libraries(msl_header_smoke_no_exceptions PRIVATE msl::msl)
    target_compile_features(msl_header_smoke_no_exceptions PRIVATE cxx_std_20)
    target_compile_definitions(msl_header_smoke_no_exceptions PRIVATE MSL_HAS_EXCEPTIONS=0)
    target_compile_options(msl_header_smoke_no_exceptions PRIVATE -Wall -Wextra -Wpedantic -fno-exceptions)
endif()
