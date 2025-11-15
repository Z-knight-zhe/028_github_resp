#include <iostream>
#include <type_traits>
// #include <typeinfo>
#if 0
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
// template <typename T, int size>
// T createArray() {
//   return T[size];
// }

// 写一个模板类Power<N, M>, 计算N^M
template <int N, int M>
class Power {
 public:
  static const int value = N * Power<N, M - 1>::value;
};

template <int N>
class Power<N, 0> {
 public:
  static const int value = 1;
};

// 增强版本：支持运行时参数检查和更好的错误处理
template <long long N, unsigned int M>
class PowerEnhanced {
  static_assert(M >= 0, "Exponent must be non-negative");

 public:
  static constexpr long long value = []() constexpr {
    if constexpr (M == 0)
      return 1LL;
    else if constexpr (M == 1)
      return N;
    else
      return N * PowerEnhanced<N, M - 1>::value;
  }();

  // 运行时计算函数
  static constexpr long long compute() { return value; }

  // 支持不同底数的运行时计算
  template <typename T>
  static constexpr T compute_runtime(T base) {
    T result = 1;
    for (unsigned int i = 0; i < M; ++i) {
      result *= base;
    }
    return result;
  }
};

int main() {
  std::cout << max(10, 20) << std::endl;      // 20
  std::cout << max(3.14, 2.71) << std::endl;  // 3.14

  auto result = add(10, 3.14);  // double, 13.14
  std::cout << result << " type: " << typeid(result).name() << std::endl;

  auto power_test = Power<2, 8>::value;  // 256
  std::cout << "2^8 = " << power_test << std::endl;

  // 测试增强版本
  std::cout << "Runtime 3^4: " << PowerEnhanced<3, 4>::compute_runtime(3.3)
            << std::endl;

  return 0;
}

#endif

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type isOdd(T value) {
  if (value % 2 == 1) {
    std::cout << value << " is odd." << std::endl;
  } else {
    std::cout << value << " is even." << std::endl;
  }
  return false;
}

int main() {
  if (isOdd(5)) {
    std::cout << "Checked oddness successfully." << std::endl;
  }

  return 0;
}