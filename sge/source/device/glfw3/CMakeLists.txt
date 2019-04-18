cmake_minimum_required(VERSION 2.8)

find_package(GLFW3 REQUIRED)

set(TARGET sge.device.glfw3)

file(GLOB_RECURSE SRC_FILES "*.c" "*.cpp" "*.cxx" )

# add target
add_library(${TARGET} SHARED ${SRC_FILES})
target_link_libraries(${TARGET} sge.core ${GLFW3_LIBRARY})
target_include_directories(${TARGET} PRIVATE .)
target_include_directories(${TARGET} SYSTEM PRIVATE ${GLFW3_INCLUDE_PATH})
target_compile_definitions(${TARGET} PRIVATE -DMODULE_DEVICE_EXPORTS)

# install target
install(TARGETS ${TARGET}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib)
