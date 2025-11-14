cmake_minimum_required(VERSION 3.10.0)
project(main VERSION 0.1.0 LANGUAGES C CXX)

# LLVM 包含路径（为可读性使用变量）
set(LLVM_INCLUDE_DIR "D:/001_software/037_llvm/llvm/include")

# 导出 compile_commands.json，便于编辑器/静态分析使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 为主程序生成可执行文件
# add_executable(main main.cpp)

# 为src/001_hello_world/hello_world.cpp生成可执行文件
add_executable(hello_world src/001_hello_world/hello_world.cpp)
target_include_directories(hello_world PRIVATE ${LLVM_INCLUDE_DIR})

# 为src/002_template/001_test.cpp生成可执行文件
add_executable(test_001 src/002_template/001_test.cpp)
target_include_directories(test_001 PRIVATE ${LLVM_INCLUDE_DIR})

include(CTest)
enable_testing()

