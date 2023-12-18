#include <gtest/gtest.h>

#include "Headers/model.h"

TEST(test, brackets) {
  s21::Model result{"(8+2)*5"};
  EXPECT_EQ(result.GetData(), 50);
}

TEST(test, addition) {
  s21::Model result{"1+1"};
  EXPECT_EQ(result.GetData(), 2);
}

TEST(test, sub) {
  s21::Model result{"6.00009-0.00003"};
  EXPECT_EQ(result.GetData(), 6.00006);
}

TEST(test, brackets1) {
  s21::Model result{"(8-(-2)*5)"};
  EXPECT_EQ(result.GetData(), 18);
}

TEST(test, addition1) {
  s21::Model result{"1.999+0.001"};
  EXPECT_EQ(result.GetData(), 2);
}

TEST(test, sub1) {
  s21::Model result{"atan(1)-6.12"};
  EXPECT_EQ(result.GetData(), atan(1) - 6.12);
}

TEST(test, brackets2) {
  s21::Model result{"(8+12)/10-2"};
  EXPECT_EQ(result.GetData(), 0);
}

TEST(test, addition2) {
  s21::Model result{"sin(1)+cos(1)"};
  EXPECT_EQ(result.GetData(), sin(1) + cos(1));
}

TEST(test, sub2) {
  s21::Model result{"100000-9"};
  EXPECT_EQ(result.GetData(), 100000 - 9);
}

TEST(test, sqrt) {
  s21::Model result{"sqrt(64)"};
  EXPECT_EQ(result.GetData(), 8);
}

TEST(test, mod) {
  s21::Model result{"3mod(2)"};
  EXPECT_EQ(result.GetData(), 1);
}

TEST(test, pow) {
  s21::Model result{"2^2"};
  EXPECT_EQ(result.GetData(), 4);
}

TEST(test, pow1) {
  s21::Model result{"2^2^3"};
  EXPECT_EQ(result.GetData(), 256);
}

TEST(test, acos) {
  s21::Model result{"acos(-0.4)"};
  EXPECT_EQ(result.GetData(), acos(-0.4));
}

TEST(test, asin) {
  s21::Model result{"asin(0.4)"};
  EXPECT_EQ(result.GetData(), asin(0.4));
}

TEST(test, tan) {
  s21::Model result{"tan(10)"};
  EXPECT_EQ(result.GetData(), tan(10));
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
