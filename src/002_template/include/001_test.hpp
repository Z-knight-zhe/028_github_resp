#pragma once

#include <array>
#include <iostream>
#include <type_traits>

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

/* SFINAE基础 */
template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type isOdd(T value) {
  if (value % 2 == 1) {
    std::cout << value << " is odd." << std::endl;
  } else {
    std::cout << value << " is even." << std::endl;
  }
  return false;
}

/* 模板部分特化 */
template <typename T>
struct RemovePointer {
  using Type = T;
};

template <typename T>
struct RemovePointer<T*> {
  using Type = T;
};

template <typename T>
void print_type_info() {
  /* 打印原始类型 */
  std::cout << "Orignal type: " << typeid(T).name() << std::endl;

  using ResultType = typename RemovePointer<T>::Type;
  std::cout << "After removing pointer type: " << typeid(ResultType).name()
            << std::endl;
}

/* 在编译器做条件选择，实现模板Conditional<B, T, F>, 根据布尔值选择类型 */
template <bool B, typename T, typename F>
struct Conditional;

template <typename T, typename F>
struct Conditional<true, T, F> {
  using Type = T;
};

template <typename T, typename F>
struct Conditional<false, T, F> {
  using Type = F;
};

/* 实现一个类型列表TypeList<Ts...>，并写一个模板Length<TypeList<...>>计算类型数量 */
template <typename... Ts>
struct TypeList {
};  // 这是一个模板结构体，它的作用是封装一众类型，不需要运行时数据和函数

template <typename TList>  // 不完整的模板类声明，
struct Length;

// 1. 引入名称，告诉编译器Lenth是一个接受一个类型参数TList的结构体模板
// 2. 防止实例化：这个通用模板没有定义，因为没有{}，这意味着如果你试图直接使用
//    这意味着如果你试图直接使用Length<SomeType>，编译器会报错，因为无法匹配
//    任何一个特步啊版本，因为没有定义，无法实例化。
// 3. 作为特化的基础：它作为所有后续特化版本的基础签名

template <>
struct Length<TypeList<>> {
  static constexpr uint32_t value = 0;
};

/* 实现模板TypeAt<N, TypeList<...>>，获取第N个类型 */
// 递归终止条件，当传递下来的类型列表为空时，value值等于0
template <typename T, typename... Params>
struct Length<TypeList<T, Params...>> {
  static constexpr uint32_t value = 1 + Length<TypeList<Params...>>::value;
};

// 用于匹配类型列表中至少含有一个类型
// 第一个参数匹配T，其后面所有参数匹配Params...
template <int N, typename... T>
struct TypeAtPosition;

// 递归终止条件：当N = 0时，取出第一个类型即可
template <typename T, typename... Rest>
struct TypeAtPosition<0, TypeList<T, Rest...>> {
  using type = T;
};

// 递归特化模板，用来匹配非终止条件匹配参数
template <int N, typename T, typename... Rest>
struct TypeAtPosition<N, TypeList<T, Rest...>>
    : TypeAtPosition<N - 1, TypeList<Rest...>> {};

/* 写一个模板PrintNumbers<N>，在编译期打印1到N（通过递归调用静态函数实现) */
template <int N>
struct PrintHelper {
  static void print() {
    std::cout << N << std::endl;
    PrintHelper<N - 1>::print();
  }
};

template <>
struct PrintHelper<0> {
  static void print() {}
};

template <int N>
class PrintNumbers {
 public:
  static void execute() {
    std::cout << "编译器生成的数字0 ~ N" << std::endl;
    PrintHelper<N>::print();
  }
};

/* 用constexpr实现阶乘函数，并在static_assert中验证 */
template <int N>
struct Factorial {
  static constexpr uint32_t value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
  static constexpr uint32_t value = 1;
};

/* 使用if constexpr */
template <typename T>
void PrintInfo(T value) {
  if constexpr (std::is_integral_v<T>) {
    std::cout << "整数：" << value << std::endl;
  } else if constexpr (std::is_floating_point_v<T>) {
    std::cout << "浮点数：" << value << std::endl;
  } else {
    std::cout << "其他类型：" << value << std::endl;
  }
}

/* 实现一个模板SumSequence，利用std::integer_sequence计算序列和。*/
template <typename T>
constexpr T SumSequence(std::integer_sequence<T>) {
  return T{};
}

template <typename T, T first, T... remain>
constexpr T SumSequence(std::integer_sequence<T, first, remain...>) {
  return first + SumSequence(std::integer_sequence<T, remain...>());
}

/* concept 约束模板参数 C++20 */

/* 实现IsPointer<T> 检测指针类型 */
template <typename T>
struct IsPointer {
  constexpr static bool value = false;
};

template <typename T>
struct IsPointer<T*> {
  constexpr static bool value = true;
};

/**
 * @brief 编译期固定大小的二维矩阵。
 * * @tparam T 矩阵中元素的类型。
 * @tparam Rows 矩阵的行数 (非类型模板参数)。
 * @tparam Cols 矩阵的列数 (非类型模板参数)。
 */
template <typename T, size_t row, size_t col>
class CompileTimeMartix {
 private:
  std::array<T, row * col> data_;

  constexpr std::size_t GetIndex(std::size_t i, std::size_t j) const {
    if (i >= row || j >= col) {
      throw std::out_of_range("Martix index out of bounds.");
    }
    return i * row + j;
  }

 public:
  CompileTimeMartix() = default;

  constexpr T& get(std::size_t i, std::size_t j) {
    return data_[GetIndex(i, j)];
  }

  constexpr static size_t GetRow() { return row; }

  constexpr static size_t GetCol() { return col; }
};