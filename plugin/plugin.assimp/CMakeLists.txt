cmake_minimum_required (VERSION 3.8)

if(WIN32)
    set(ASSIMP_ROOT_DIR "${PROJECT_SOURCE_DIR}/3rd/assimp")
    install(DIRECTORY "${ASSIMP_ROOT_DIR}/bin/${PLATFORM}/" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif(WIN32)
find_package(ASSIMP REQUIRED)
message(status "Found ASSIMP in ${ASSIMP_LIBRARIES}")

include_directories(${CMAKE_SOURCE_DIR}/include ${ASSIMP_INCLUDE_PATH})

file(GLOB_RECURSE SRC_FILES "src/*.c" "src/*.cpp" "src/*.cxx")

add_library(plugin.assimp SHARED ${SRC_FILES})
target_link_libraries(plugin.assimp ${ASSIMP_LIBRARIES})
