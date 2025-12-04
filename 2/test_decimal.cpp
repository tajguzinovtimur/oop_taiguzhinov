#include <gtest/gtest.h>
#include "decimal.h"

TEST(DecimalTest, DefaultConstructor) {
    Decimal d;
    EXPECT_EQ(d.toString(), "0");
    EXPECT_EQ(d.getSize(), 1);
}

TEST(DecimalTest, StringConstructor) {
    Decimal d("12345");
    EXPECT_EQ(d.toString(), "12345");
    EXPECT_EQ(d.getDigit(0), '5');
    EXPECT_EQ(d.getDigit(4), '1');
}

TEST(DecimalTest, StringConstructorInvalid) {
    EXPECT_THROW(Decimal("12a34"), std::invalid_argument);
    EXPECT_THROW(Decimal(""), std::invalid_argument);
}

TEST(DecimalTest, SizeConstructor) {
    Decimal d(5, '3');
    EXPECT_EQ(d.toString(), "33333");
    EXPECT_EQ(d.getSize(), 5);
}

TEST(DecimalTest, CopyConstructor) {
    Decimal d1("9876");
    Decimal d2(d1);
    EXPECT_EQ(d2.toString(), "9876");
}

TEST(DecimalTest, MoveConstructor) {
    Decimal d1("12345");
    Decimal d2(std::move(d1));
    EXPECT_EQ(d2.toString(), "12345");
    EXPECT_EQ(d1.getSize(), 0);
}

TEST(DecimalTest, AddOperation) {
    Decimal d1("123");
    Decimal d2("456");
    Decimal result = d1.add(d2);
    EXPECT_EQ(result.toString(), "579");
}

TEST(DecimalTest, AddWithCarry) {
    Decimal d1("999");
    Decimal d2("1");
    Decimal result = d1.add(d2);
    EXPECT_EQ(result.toString(), "1000");
}

TEST(DecimalTest, SubtractOperation) {
    Decimal d1("1000");
    Decimal d2("123");
    Decimal result = d1.subtract(d2);
    EXPECT_EQ(result.toString(), "877");
}

TEST(DecimalTest, SubtractInvalid) {
    Decimal d1("100");
    Decimal d2("200");
    EXPECT_THROW(d1.subtract(d2), std::invalid_argument);
}

TEST(DecimalTest, AddAssign) {
    Decimal d1("100");
    Decimal d2("200");
    d1.addAssign(d2);
    EXPECT_EQ(d1.toString(), "300");
}

TEST(DecimalTest, SubtractAssign) {
    Decimal d1("500");
    Decimal d2("123");
    d1.subtractAssign(d2);
    EXPECT_EQ(d1.toString(), "377");
}

TEST(DecimalTest, Equals) {
    Decimal d1("12345");
    Decimal d2("12345");
    Decimal d3("12346");
    
    EXPECT_TRUE(d1.equals(d2));
    EXPECT_FALSE(d1.equals(d3));
}

TEST(DecimalTest, LessThan) {
    Decimal d1("123");
    Decimal d2("456");
    Decimal d3("1230");
    
    EXPECT_TRUE(d1.lessThan(d2));
    EXPECT_TRUE(d1.lessThan(d3));
    EXPECT_FALSE(d2.lessThan(d1));
}

TEST(DecimalTest, GreaterThan) {
    Decimal d1("456");
    Decimal d2("123");
    Decimal d3("45");
    
    EXPECT_TRUE(d1.greaterThan(d2));
    EXPECT_TRUE(d1.greaterThan(d3));
    EXPECT_FALSE(d2.greaterThan(d1));
}

TEST(DecimalTest, RemoveLeadingZeros) {
    Decimal d("00012300");
    EXPECT_EQ(d.toString(), "12300");
    
    Decimal d2("0000");
    EXPECT_EQ(d2.toString(), "0");
}

TEST(DecimalTest, AssignmentOperators) {
    Decimal d1("12345");
    Decimal d2;
    d2 = d1;
    EXPECT_EQ(d2.toString(), "12345");
    
    Decimal d3;
    d3 = std::move(d1);
    EXPECT_EQ(d3.toString(), "12345");
}