﻿#
# Try to find GLFW library and include path.
# Once done this will define
#
# GLFW3_FOUND
# GLFW3_INCLUDE_PATH
# GLFW3_LIBRARY
# 

IF(WIN32)
    FIND_PATH( GLFW3_INCLUDE_PATH GLFW/glfw3.h
		${GLFW_ROOT_DIR}/include
		${PROJECT_SOURCE_DIR}/3rd/GLFW3/include
		${CMAKE_CURRENT_SOURCE_DIR}/3rd/GLFW3/include
		DOC "The directory where GLFW/glfw3.h resides")
        
    if (CMAKE_SIZEOF_VOID_P EQUAL 8) # x64
		set(PLATFORM x64)
	else() # x86
		set(PLATFORM Win32)
	endif()
        
    FIND_LIBRARY( GLFW3_LIBRARY
        NAMES glfw3 GLFW
        PATHS
		${GLFW_ROOT_DIR}/lib/${PLATFORM}
        ${PROJECT_SOURCE_DIR}/3rd/GLFW3/lib/${PLATFORM}
        ${CMAKE_CURRENT_SOURCE_DIR}/3rd/GLFW3/lib/${PLATFORM}
        DOC "The GLFW library")
        
ELSE(WIN32)
	FIND_PATH( GLFW3_INCLUDE_PATH GLFW/glfw3.h
		/usr/include
		/usr/local/include
		/sw/include
        /opt/local/include
		${GLFW_ROOT_DIR}/include
		DOC "The directory where GLFW/glfw3.h resides")

	# Prefer the static library.
	FIND_LIBRARY( GLFW3_LIBRARY
        NAMES libGLFW.a GLFW libGLFW3.a GLFW3 libglfw.so libglfw.so.3 libglfw.so.3.0
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		${GLFW_ROOT_DIR}/lib
		DOC "The GLFW library")
ENDIF(WIN32)

SET(GLFW3_FOUND "NO")
IF(GLFW3_INCLUDE_PATH AND GLFW3_LIBRARY)
	SET(GLFW_LIBRARIES ${GLFW3_LIBRARY})
	SET(GLFW3_FOUND "YES")
    message(STATUS "Found GLFW: ${GLFW_LIBRARIES}")
ENDIF(GLFW3_INCLUDE_PATH AND GLFW3_LIBRARY)
