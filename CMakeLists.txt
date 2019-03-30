cmake_minimum_required (VERSION 3.8)

project ("GLEngine")

# 检查是否设置构建类型
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

# 设置模块查找目录
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 跨平台用难得改，直接消除不安全函数警告
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# 链接到OpenGL库
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARIES})

# 查找GLFW库
find_package(GLFW3 REQUIRED)
include_directories(${GLFW3_INCLUDE_PATH})

# 查找GLEW库
if(WIN32)
    set(GLEW_DIR "${PROJECT_SOURCE_DIR}/3rd/glew-2.1.0")
    if (CMAKE_SIZEOF_VOID_P EQUAL 8) # x64
        set(PLATFORM x64)
    else() # Win32
        set(PLATFORM Win32)
    endif()
    list(APPEND CMAKE_PREFIX_PATH ${GLEW_DIR})
    list(APPEND CMAKE_LIBRARY_PATH "${GLEW_DIR}/lib/Release/${PLATFORM}")
    install (FILES "${GLEW_DIR}/bin/Release/${PLATFORM}/glew32.dll" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif(WIN32)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

# 包含引擎
include_directories(sge/include)
add_subdirectory ("sge")

# 链接到引擎
link_libraries(sge)

# 包含其他目录
add_subdirectory ("applications")
