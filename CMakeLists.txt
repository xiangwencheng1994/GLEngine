# CMakeList.txt : 顶级 CMake 项目文件，执行全局配置
# 和此处的包含子项目。
#
cmake_minimum_required (VERSION 2.8)

project ("GLEngine")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

# 包含子项目。
add_subdirectory ("src")
add_subdirectory ("demo1")
