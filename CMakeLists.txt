cmake_minimum_required (VERSION 3.8)

project ("sge")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_TEST "Build the test program"  ON)
IF(BUILD_TEST)
    enable_testing()
ENDIF()

set(SGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sge/include)
message("SGE_INCLUDE_DIR: ${SGE_INCLUDE_DIR}")

include_directories(SYSTEM ${SGE_INCLUDE_DIR})

add_subdirectory("sge")

add_custom_target(CopyAsset ALL)
add_custom_command(TARGET CopyAsset POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
install(DIRECTORY assets/ DESTINATION assets)

# 包含插件目录
# add_subdirectory("plugin")

# 包含其他目录
add_subdirectory ("applications")
