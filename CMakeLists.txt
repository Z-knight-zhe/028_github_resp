cmake_minimum_required(VERSION 3.14)
project(main VERSION 0.1.0 LANGUAGES C CXX)

# LLVM 包含路径（为可读性使用变量）
set(LLVM_INCLUDE_DIR "D:/001_software/037_llvm/llvm/include")

# 导出 compile_commands.json，便于编辑器/静态分析使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

# GoogleTest integration
include(GNUInstallDirs)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(3rd_lib/googletest)

# 递归添加 src 下所有子目录
file(GLOB children RELATIVE "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/src/*")
foreach(child ${children})
    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/src/${child}")
        add_subdirectory("src/${child}")
    endif()
endforeach()

