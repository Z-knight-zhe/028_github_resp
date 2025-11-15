#include <gtest/gtest.h>

// 简单示例测试：验证算术
TEST(SmokeTest, BasicAssertions) {
  EXPECT_EQ(1 + 1, 2);
}

// 如果您希望测试项目中的函数，建议把要测试的函数抽到头文件/源文件中并在这里包含
// 例如：#include "../002_template/some_header.h"
