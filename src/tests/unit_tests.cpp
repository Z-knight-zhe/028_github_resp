#include <gtest/gtest.h>
#include <type_traits>
#include "../002_template/include/001_test.hpp"

TEST(TemplateTest, IsOdd) {
  if (isOdd(5)) {
    std::cout << "Checked oddness successfully." << std::endl;
  }
}

TEST(TemplateTest, RemovePointer) {
  print_type_info<int*>();
  print_type_info<double**>();
  print_type_info<int>();
}

TEST(TemplateTest, Conditional) {
  using type1 = Conditional<true, int, double>::Type;
  EXPECT_TRUE((std::is_same<type1, int>::value));
  using type2 = Conditional<false, char, short>::Type;
  EXPECT_TRUE((std::is_same<type2, short>::value));
}

TEST(TemplateTest, Length) {
  using MyTypes = TypeList<int, double, char, float>;
  EXPECT_EQ(Length<MyTypes>::value, 4);

  using EmptyTypes = TypeList<>;
  EXPECT_EQ(Length<EmptyTypes>::value, 0);
}

TEST(TemplateTest, TypeAtPosition) {
  using TypeList1 = TypeList<int, char, double, short>;

  using ResultType0 = TypeAtPosition<0, TypeList1>::type;
  using ResultType2 = TypeAtPosition<2, TypeList1>::type;

  EXPECT_FALSE((std::is_same_v<char, ResultType0>));
  EXPECT_TRUE((std::is_same_v<double, ResultType2>));
}

TEST(TemplateTest, PrintNum) {
  PrintNumbers<10>::execute();
}

static_assert(Factorial<5>::value == 120, "5, should be 120");

TEST(TemplateTest, Fabonaci) {
  EXPECT_EQ(720, Factorial<6>::value);
}

TEST(TemplateTest, PrintInfo) {
  PrintInfo<int>(10);
  PrintInfo<float>(3.14);
  PrintInfo("C++");
}

TEST(TemplateTest, SequenceSum) {
  constexpr auto seq = std::make_integer_sequence<int, 100>();
  constexpr auto result = SumSequence(seq);
  std::cout << "result = " << std::dec << result << std::endl;
  EXPECT_EQ(4950, result);
}

TEST(TemplateTest, IsPointer) {
  using ptr = IsPointer<int*>;
  using non_ptr = IsPointer<int>;

  EXPECT_TRUE(ptr::value);
  EXPECT_FALSE(non_ptr::value);
}

TEST(TemplateTest, CompileTimeMartix) {
  CompileTimeMartix<int, 4, 5> martix;

  martix.get(0, 0) = 100;
  martix.get(0, 1) = 88;
  martix.get(3, 3) = 66;
  martix.get(2, 4) = 7;

  for (uint32_t i = 0; i < 4; i++) {
    for (uint32_t j = 0; j < 5; j++) {
      std::cout << martix.get(i, j) << "\t";
    }
    std::cout << std::endl;
  }

  std::cout << "Martix Row = " << std::dec << martix.GetRow() << std::endl;
  std::cout << "Martix Col = " << std::dec << martix.GetCol() << std::endl;
}