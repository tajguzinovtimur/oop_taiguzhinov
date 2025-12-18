cmake_minimum_required(VERSION 3.10)
project(Lab03_OOP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(main
    src/main.cpp
    src/Figure.cpp
    src/Rectangle.cpp
    src/Trapezoid.cpp
    src/Rhombus.cpp
)

target_include_directories(main PRIVATE include)


if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
    add_subdirectory(tests)
endif()