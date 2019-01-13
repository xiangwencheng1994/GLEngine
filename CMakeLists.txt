cmake_minimum_required (VERSION 2.8)

project ("SGE_ENGINE")

option(USE_OPENGLES "Use OpenGLES instead of desktop OpenGL")
SET(USE_OPENGLES OFF)

if(USE_OPENGLES)
    add_definitions(-DOPENGLES -DGL_GLEXT_PROTOTYPES)
endif(USE_OPENGLES)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_subdirectory(3rd)

set(GL_INCLUDES)
set(GL_LIBRARIES)
if(USE_OPENGLES)
	set(GL_LIBRARIES 		${GL_LIBRARIES} GLESv2 EGL)
else()
	find_package(OpenGL REQUIRED)
	set(GL_INCLUDES	${GL_INCLUDES} ${OPENGL_INCLUDE_DIR})
	set(GL_LIBRARIES ${GL_LIBRARIES} ${OPENGL_LIBRARIES} glew32)
endif()

message("GL_INCLUDES: ${GL_INCLUDES}")
message("GL_LIBRARIES: ${GL_LIBRARIES}")

add_subdirectory(sge)
add_subdirectory(App)