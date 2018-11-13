cmake_minimum_required (VERSION 2.8)

project(App)

add_definitions(-DUSE_SSE2 ${GL_DEFINES})

include_directories(../sge/include ${GL_INCLUDES})

file(GLOB SRC_FILES "source/*.cpp"
					"source/*/*.cpp"
					"source/*/*/*.cpp"
					"source/*/*/*/*.cpp")

add_executable(App ${SRC_FILES})
target_link_libraries(App sge ${GL_LIBRARIES})

install(TARGETS App RUNTIME DESTINATION .)
