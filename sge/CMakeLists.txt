cmake_minimum_required(VERSION 2.8)

set(TARGET sge)

set(SGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

set(SGE_SOURCE_LIST)
set(SGE_LINK_LIBS)

# add core source file
file(GLOB_RECURSE SGE_SRC_CORE "${SGE_SOURCE_DIR}/core/*.c" "${SGE_SOURCE_DIR}/core/*.cpp")
list(APPEND SGE_SOURCE_LIST ${SGE_SRC_CORE})
message("add core module")

# add asset source file
file(GLOB_RECURSE SGE_ASSET_CORE "${SGE_SOURCE_DIR}/asset/*.c" "${SGE_SOURCE_DIR}/asset/*.cpp")
list(APPEND SGE_SOURCE_LIST ${SGE_ASSET_CORE})
message("add asset module")


# add target
add_library(${TARGET} SHARED ${SGE_SOURCE_LIST})
target_link_libraries(${TARGET} ${SGE_LINK_LIBS})
target_include_directories(${TARGET} PUBLIC ${SGE_INCLUDE_DIR})
target_include_directories(${TARGET} PRIVATE ${SGE_SOURCE_DIR})

# install target
install(TARGETS ${TARGET}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib)

