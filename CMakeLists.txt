cmake_minimum_required(VERSION 3.14)
project(LogosContainer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build src first
add_subdirectory(src)

# The "none" container implementation (packages.<system>.none).
add_subdirectory(none)

# Opt-out, so the none package builds where there is no gtest (a cross build).
option(LOGOS_CONTAINER_BUILD_TESTS "Build the logos-container tests" ON)

if(LOGOS_CONTAINER_BUILD_TESTS)

# GoogleTest setup
# Try to find GoogleTest via find_package first (for Nix and system installations)
find_package(GTest QUIET)

if(NOT GTest_FOUND)
    # Fall back to FetchContent if GoogleTest is not found
    message(STATUS "GoogleTest not found via find_package, using FetchContent")
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)
else()
    message(STATUS "Using system GoogleTest")
endif()

enable_testing()
include(GoogleTest)

# Add tests subdirectory
add_subdirectory(tests)

endif()  # LOGOS_CONTAINER_BUILD_TESTS

# Header-only contract: nothing to install but the headers (mirrors
# process-stats so consumers use <logos_container/module_container.h>).
install(DIRECTORY src/logos_container/ DESTINATION include/logos_container
    FILES_MATCHING PATTERN "*.h"
)
