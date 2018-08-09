cmake_minimum_required (VERSION 2.8)

project(App)

if(NOT SGE_INCLUDE_DIRS OR NOT SGE_LIBS)
	find_package(SGE REQUIRED)
endif()

include_directories(${SGE_INCLUDE_DIRS})

aux_source_directory(. sources)

add_executable(App ${sources})
target_link_libraries(App ${SGE_LIBS})

install(TARGETS App RUNTIME DESTINATION bin)
