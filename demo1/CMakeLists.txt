# CMakeList.txt: demoe 的 CMake 项目，包括源和定义
# 此处特定于项目的逻辑。
#
cmake_minimum_required (VERSION 2.8)

find_package(OpenGL REQUIRED)
include_directories(../include ${OPENGL_INCLUDE_DIR})

aux_source_directory(. SOURCES)

# 将源添加到此项目的可执行文件。
add_executable(demo1 ${SOURCES})
target_link_libraries(demo1 GLEngine ${OPENGL_LIBRARIES})

install(TARGETS demo1 RUNTIME DESTINATION bin)