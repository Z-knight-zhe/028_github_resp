#include <iostream>

#include <typeinfo>

// 基础函数模板
template <typename T>
T max(T a, T b) {
  return (a > b) ? a : b;
}

// 多类型参数的函数模板
template <typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
  return a + b;
}

// 非类型模板参数
template <typename T, int size>
T createArray() {
  return T[size];
}

int main() {
  std::cout << max(10, 20) << std::endl;      // 20
  std::cout << max(3.14, 2.71) << std::endl;  // 3.14

  auto result = add(10, 3.14);  // double, 13.14
  std::cout << result << " type: " << typeid(result).name() << std::endl;

  return 0;
}