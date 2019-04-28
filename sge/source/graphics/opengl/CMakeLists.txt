cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)

set(TARGET sge.graphics.opengl)

file(GLOB_RECURSE SRC_FILES "*.c" "*.cpp" "*.cxx" )

# add target
add_library(${TARGET} SHARED ${SRC_FILES})
target_link_libraries(${TARGET} sge.core ${OPENGL_LIBRARIES})
target_include_directories(${TARGET} PRIVATE .)
target_include_directories(${TARGET} SYSTEM PRIVATE ${OPENGL_INCLUDE_DIR})
target_compile_definitions(${TARGET} PRIVATE -DMODULE_GRAPHICS_EXPORTS -DGLEW_STATIC)

# install target
install(TARGETS ${TARGET}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib)
