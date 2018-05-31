# CMakeList.txt: GLEngine 的 CMake 项目，包括源和定义
# 此处特定于项目的逻辑。
#
cmake_minimum_required (VERSION 2.8)

find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(../include
		${FREETYPE_INCLUDE_DIRS}
		${OPENGL_INCLUDE_DIR})

aux_source_directory(. SOURCES)

add_definitions("-DGLEngine_EXPORTS")

# 将源添加到此项目的可执行文件。
add_library(GLEngine SHARED ${SOURCES})
target_link_libraries(GLEngine
		${FREETYPE_LIBRARIES}
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARIES})

install(TARGETS GLEngine
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)

file(GLOB headers "../include/*.h")
file(GLOB headers "../include/glew/*.h")

install(FILES ${headers} DESTINATION "${CMAKE_BINARY_DIR}/include")
