cmake_minimum_required(VERSION 3.10)
project(Lab4_OOP_Variant21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(lab4_main src/main.cpp)


target_include_directories(lab4_main PRIVATE include)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lab4_main PRIVATE -Wall -Wextra -Wno-non-template-friend)
endif()