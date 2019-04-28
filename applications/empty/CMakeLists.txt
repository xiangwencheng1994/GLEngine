cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SRC_FILES "src/*.c" "src/*.cpp" "src/*.cxx")

add_executable(empty ${SRC_FILES})
target_link_libraries(empty sge)