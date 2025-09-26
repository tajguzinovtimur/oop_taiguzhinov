#include <gtest/gtest.h>
#include "../headers/function.h"

TEST(CountVowelsTest, EmptyString) {
    EXPECT_EQ(count_vowels(""), 0);
}

TEST(CountVowelsTest, NoVowels) {
    EXPECT_EQ(count_vowels("bcdfghjklmnpqrstvwxz"), 0);
    EXPECT_EQ(count_vowels("1234567890!@#$%"), 0);
}

TEST(CountVowelsTest, AllVowels) {
    EXPECT_EQ(count_vowels("aeiouy"), 6);
    EXPECT_EQ(count_vowels("aeiouyaeiouy"), 12);
}

TEST(CountVowelsTest, MixedCharacters) {
    EXPECT_EQ(count_vowels("hello world"), 3);
    EXPECT_EQ(count_vowels("programming is fun"), 5);
}

TEST(CountVowelsTest, WithSpaces) {
    EXPECT_EQ(count_vowels("a e i o u y"), 6);
    EXPECT_EQ(count_vowels("hello there"), 4);
}