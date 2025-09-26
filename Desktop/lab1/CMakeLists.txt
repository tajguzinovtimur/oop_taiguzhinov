cmake_minimum_required(VERSION 3.14)
project(VowelCounter)

set(CMAKE_CXX_STANDARD 11)

set(GTEST_DIR "${CMAKE_SOURCE_DIR}/googletest" CACHE PATH "Path to Google Test")

if(EXISTS ${GTEST_DIR}/CMakeLists.txt)
    message(STATUS "Found GoogleTest at: ${GTEST_DIR}")
    add_subdirectory(${GTEST_DIR} googletest-build)
else()
    message(FATAL_ERROR "GoogleTest not found at: ${GTEST_DIR}. Please check the path.")
endif()

add_executable(vowel_counter 
    src/main.cpp 
    src/function.cpp
)
target_include_directories(vowel_counter PRIVATE headers)

add_subdirectory(tests)