cmake_minimum_required(VERSION 2.8)

set(TARGET sge.core)

file(GLOB_RECURSE SRC_FILES "*.c" "*.cpp" "*.cxx" )

# add target
add_library(${TARGET} SHARED ${SRC_FILES})
target_link_libraries(${TARGET})
target_include_directories(${TARGET} PRIVATE .)
target_compile_definitions(${TARGET} PRIVATE -DMODULE_CORE_EXPORTS)

# install target
install(TARGETS ${TARGET}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib)
