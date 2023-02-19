# CMakeLists file for using the Google Test Framework
# Based on the gtest cmake example

cmake_minimum_required(VERSION 3.25)
project(digichess-tests)

set(INC_DIR "include")
set(SRC_DIR "src")
set(TEST_DIR "tests")

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg

FILE(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_DIR}" "${TEST_DIR}/*.test.cpp")
set(SRC_FILES ${TEST_FILES})

list(TRANSFORM TEST_FILES PREPEND "${TEST_DIR}/")
list(TRANSFORM SRC_FILES PREPEND "${SRC_DIR}/")
list(TRANSFORM SRC_FILES REPLACE ".test.cpp" ".c")

add_executable(digichess-tests ${SRC_FILES} ${TEST_FILES})
target_include_directories(digichess-tests PUBLIC ${INC_DIR})
target_link_libraries(digichess-tests gtest_main)