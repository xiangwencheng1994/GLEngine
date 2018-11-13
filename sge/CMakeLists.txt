cmake_minimum_required (VERSION 2.8)

project(sge)

add_definitions(-DUSE_SSE2)

include_directories(${GL_LIBRARIES} include)

file(GLOB SRC_FILES "source/*.cpp"
					"source/*/*.cpp"
					"source/*/*/*.cpp"
					"source/*/*/*/*.cpp")
					
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${GL_LIBRARIES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)