cmake_minimum_required (VERSION 3.8)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES "src/*.c" "src/*.cpp" "src/*.cxx")

add_library(sge SHARED ${SRC_FILES})
target_link_libraries(sge ${GLFW3_LIBRARY})