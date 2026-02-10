cmake_minimum_required(VERSION 3.20)

project(lethimcook
    VERSION 1.0.0
    DESCRIPTION "A unit conversion library for cooking"
    LANGUAGES CXX
)

# C++20 standard requirements
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Define the static library target
add_library(lethimcook STATIC
    src/units.cpp
    src/converter.cpp
    src/natural.cpp
    src/recipe.cpp
)

# Set include directories with generator expressions for build and install
target_include_directories(lethimcook
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Define the CLI executable
add_executable(lethimcook_cli cli/main.cpp)
target_link_libraries(lethimcook_cli PRIVATE lethimcook)

# Fetch GoogleTest for testing
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Include GoogleTest module for test discovery
include(GoogleTest)

# Create test executables
add_executable(test_converter tests/test_converter.cpp)
target_link_libraries(test_converter PRIVATE lethimcook GTest::gtest_main)
gtest_discover_tests(test_converter)

add_executable(test_natural tests/test_natural.cpp)
target_link_libraries(test_natural PRIVATE lethimcook GTest::gtest_main)
gtest_discover_tests(test_natural)

add_executable(test_recipe tests/test_recipe.cpp)
target_link_libraries(test_recipe PRIVATE lethimcook GTest::gtest_main)
gtest_discover_tests(test_recipe)
