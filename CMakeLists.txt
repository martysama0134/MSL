cmake_minimum_required(VERSION 3.23)

project(
    MSL
    VERSION 4.1.0
    DESCRIPTION "Marty Support Library (header-only C++20 utilities)"
    LANGUAGES CXX
)

option(MSL_BUILD_TESTS "Build deterministic MSL test suite" ON)
option(MSL_BUILD_EXAMPLES "Build MSL example programs" OFF)

add_library(msl INTERFACE)
add_library(msl::msl ALIAS msl)

target_compile_features(msl INTERFACE cxx_std_20)
target_include_directories(
    msl
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    TARGETS msl
    EXPORT MSLTargets
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT MSLTargets
    FILE MSLTargets.cmake
    NAMESPACE msl::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MSL
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/MSLConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MSLConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MSL
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MSLConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MSLConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/MSLConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MSL
)

if(MSL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(MSL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
