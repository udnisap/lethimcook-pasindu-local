cmake_minimum_required(VERSION 3.20)

project(lethimcook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Static Library ---
add_library(lethimcook STATIC
    src/units.cpp
    src/converter.cpp
)

target_include_directories(lethimcook
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# --- CLI Executable ---
add_executable(lethimcook_cli cli/main.cpp)
target_link_libraries(lethimcook_cli PRIVATE lethimcook)

# --- Testing ---
option(LETHIMCOOK_BUILD_TESTS "Build tests" ON)

if(LETHIMCOOK_BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    # Prevent overriding parent project compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # Test executable for converter tests
    add_executable(test_converter tests/test_converter.cpp)
    target_link_libraries(test_converter PRIVATE lethimcook GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(test_converter)
endif()
