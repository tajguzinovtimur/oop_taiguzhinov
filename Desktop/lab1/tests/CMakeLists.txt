add_executable(
  vowel_counter_tests
  test_function.cpp
  ../src/function.cpp
)

target_include_directories(vowel_counter_tests 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/headers
)

target_link_libraries(
  vowel_counter_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(vowel_counter_tests)