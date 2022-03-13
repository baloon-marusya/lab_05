// Copyright 2021 Melnikova Maria <dandelion.m@mail.ru>

#include <gtest/gtest.h>
#include <stdexcept>

#include "non_copied_stack.hpp"
#include "non_copied_stack_2.hpp"


class copied_class {
 public:
  copied_class() = default;
  copied_class(copied_class &&a) noexcept = default;
  copied_class(const copied_class &a) = default;
};

class non_copied_class {
 private:
  int _val1;
  int _val2;
 public:
  non_copied_class() = default;
  non_copied_class(int a, int b)
      : _val1(a)
      , _val2(b) {};
  non_copied_class(non_copied_class &&a) noexcept = default;
  auto operator=(non_copied_class &&a) noexcept -> non_copied_class & = default;
  non_copied_class(const non_copied_class &a) = delete;
  auto operator=(const non_copied_class &a) -> non_copied_class & = delete;
  int get_val1() const {
    return _val1;
  }
  int get_val2() const {
    return _val2;
  }
};

TEST(non_copied_class, TestConstructible)
{
  EXPECT_TRUE(std::is_move_constructible<non_copied_class>::value);
  EXPECT_FALSE(std::is_copy_constructible<non_copied_class>::value);
}

TEST(copied_class, TestConstructible)
{
  EXPECT_TRUE(std::is_move_constructible<copied_class>::value);
  EXPECT_TRUE(std::is_copy_constructible<copied_class>::value);
}

TEST(non_copied_stack, TestMovableAndCopied)
{
  EXPECT_TRUE(std::is_move_constructible<non_copied_stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<non_copied_stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<non_copied_stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<non_copied_stack<int>>::value);
}

TEST(non_copi_stack_2, TestMovableAndCopied)
{
  EXPECT_TRUE(std::is_move_constructible<non_copied_stack_2<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<non_copied_stack_2<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<non_copied_stack_2<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<non_copied_stack_2<int>>::value);
}


TEST(non_copied_stack, TestFunctionality) {
  non_copied_stack<int> stack;
  int value1 = 10;
  int value2 = 20;
  stack.push(value1);
  EXPECT_EQ(stack.head(), value1);
  stack.push(value2);
  EXPECT_EQ(stack.head(), value2);
  stack.pop();
  EXPECT_EQ(stack.head(), value1);
  stack.pop();
  EXPECT_THROW(stack.pop(), std::exception);
}

TEST(non_copied_stack_2, TestFunctionality) {
  non_copied_stack_2<non_copied_class> stack;
  int a = 10;
  int b = 20;
  stack.push_emplace(a, b);
  stack.push(non_copied_class(25, 40));
  EXPECT_EQ(stack.head().get_val1(), 25);
  EXPECT_EQ(stack.head().get_val2(), 40);
  stack.pop();
  EXPECT_EQ(stack.head().get_val1(), a);
  EXPECT_EQ(stack.head().get_val2(), b);
  stack.pop();
  EXPECT_THROW(stack.pop(), std::exception);
}
