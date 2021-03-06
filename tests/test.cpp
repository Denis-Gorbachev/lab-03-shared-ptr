// Copyright 2021 Your Name <your_email>

#include <stdexcept>

#include <gtest/gtest.h>

#include <shared_ptr.hpp>

TEST(constructor_tests, default_constructor) {
  SharedPtr<int> pointer;
  EXPECT_EQ(pointer.get(), nullptr);
}
TEST(constructor_tests, parameters_constructor)
{
  int *p = new int(9);
  SharedPtr<int> pointer(p);
  EXPECT_EQ(p, pointer.get());
  delete p;
}
TEST(constructor_tests, copy_constructor)
{
  int *p = new int(9);
  SharedPtr<int> pointer1(p);
  SharedPtr<int> pointer2(pointer1);
  //EXPECT_EQ(pointer1, pointer2);
  EXPECT_EQ(pointer1.use_count(), 2);
  delete p;
}
TEST(constructor_tests, move_copy_tests)
{
  EXPECT_EQ(std::is_move_constructible<SharedPtr<int>>::value, true);
  EXPECT_EQ(std::is_copy_constructible<SharedPtr<int>>::value, true);
}
TEST(method_tests, get)
{
  int *p = new int(9);
  SharedPtr<int> pointer1(p);
  EXPECT_EQ(pointer1.get(), p);
  delete p;
}
TEST(operator_tests, operator1)
{
  int *p = new int(9);
  SharedPtr<int> pointer1(p);
  SharedPtr<int> pointer2 = pointer1;
  EXPECT_EQ(pointer1.get(), pointer2.get());
  delete p;
}
TEST(operator_tests, operator3)
{
  int *p = new int(9);
  SharedPtr<int> pointer1(p);
  EXPECT_EQ(*pointer1, 9);
  delete p;
}
TEST(methods_tests, reset)
{
  int *p = new int(9);
  SharedPtr<int> pointer1(p);
  pointer1.reset();
  EXPECT_EQ(pointer1.get(), nullptr);
  delete p;
}
TEST(methods_tests, swap)
{
  int *p1 = new int(9);
  int *p2 = new int(10);
  SharedPtr<int> pointer1(p1);
  SharedPtr<int> pointer2(p2);
  pointer1.swap(pointer2);
  EXPECT_EQ(pointer1.get(), p2);
  EXPECT_EQ(pointer2.get(), p1);
  delete p1;
  delete p2;
}
TEST(methods_tests, use_count)
{
  int *p1 = new int(9);
  SharedPtr<int> pointer1(p1);
  EXPECT_EQ(pointer1.use_count(), 1);
  delete p1;
}
