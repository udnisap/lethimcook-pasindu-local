cmake_minimum_required(VERSION 3.20)

project(lethimcook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Static library ──────────────────────────────────────────────────────────
add_library(lethimcook_lib STATIC
    src/units.cpp
    src/converter.cpp
)

target_include_directories(lethimcook_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# ── CLI executable ──────────────────────────────────────────────────────────
add_executable(lethimcook_cli cli/main.cpp)
target_link_libraries(lethimcook_cli PRIVATE lethimcook_lib)

# ── Testing ─────────────────────────────────────────────────────────────────
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_converter tests/test_converter.cpp)
target_link_libraries(test_converter PRIVATE lethimcook_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_converter)
