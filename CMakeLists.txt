cmake_minimum_required(VERSION 3.10.0)
project(main VERSION 0.1.0 LANGUAGES C CXX)

# 设置LLVM的包含路径
include_directories("D:/001_software/037_llvm/llvm/include")

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)

include(CTest)
enable_testing()

