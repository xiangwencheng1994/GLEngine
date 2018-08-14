cmake_minimum_required (VERSION 2.8)

project ("sge")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

find_package(OpenGL REQUIRED)

include_directories(include ${OPENGL_INCLUDE_DIR})

aux_source_directory(src SGE_SOURCES)
aux_source_directory(src/imgui IMGUI_SOURCES)

add_definitions(-DUSE_SSE2)

add_library(sge SHARED ${SGE_SOURCES} ${IMGUI_SOURCES})
target_link_libraries(sge
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARIES})

install(TARGETS sge
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
		
install(DIRECTORY res/ DESTINATION bin)

install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(FILES "FindSGE.cmake" DESTINATION .)

set(SGE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
set(SGE_LIBS sge ${OPENGL_LIBRARIES})

add_subdirectory(application)