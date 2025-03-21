#include "lab2.cpp"
#include <stdexcept>
#include <gtest/gtest.h>

namespace {
TEST(UP_test, all_tests) {
  int f_a;
  f_a = 33;
  Uniqe_pointer<int> a(&f_a);
  EXPECT_TRUE(f_a == 33);
  auto b = std::move(a);
  EXPECT_TRUE(a.get() == NULL);
  Uniqe_pointer<int> c(std::move(b));
  EXPECT_TRUE(b.get() == NULL);
  EXPECT_TRUE(c.operator*() == 33);
  EXPECT_TRUE(c.operator->() == &f_a);
}
    TEST(SP_constructors_tests, move)
    {
        int f_a = 33;
        Shared_pointer<int> a(&f_a);
        auto b = std::move(a);
        EXPECT_TRUE(f_a == 33);
        std::size_t chk = b.use_count();
        EXPECT_TRUE(chk == (std::size_t)1);
        auto c(std::move(b));
        EXPECT_TRUE(*c == 33);
    }
    TEST(SP_constructors_tests, copy_and_others) {
      int f_a = 33;
      Shared_pointer<int> a(&f_a);
      auto b(a);
      EXPECT_TRUE(a.use_count() == b.use_count());
      std::cout << "a count is: " << a.use_count()
                << " and b count: " << b.use_count() << '\n';
      EXPECT_TRUE(*a == *b);
      auto c = b;
      EXPECT_TRUE(b.use_count() == c.use_count());
      std::cout << "b is count: " << b.use_count()
                << " and c count is: " << c.use_count() << '\n';
      EXPECT_TRUE(*b == *c);
      EXPECT_TRUE(b.get() == &f_a);
      EXPECT_TRUE(b.operator->() == &f_a);
      b.reset();
      EXPECT_TRUE(b.operator->() == nullptr);
      EXPECT_TRUE(b.use_count() == 1);
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}