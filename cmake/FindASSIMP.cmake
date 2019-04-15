#
# Try to find ASSIMP library and include path.
# Once done this will define
#
# ASSIMP_FOUND
# ASSIMP_INCLUDE_PATH
# ASSIMP_LIBRARIES
# 

IF(WIN32)
    FIND_PATH( ASSIMP_INCLUDE_PATH assimp/types.h
		${ASSIMP_ROOT_DIR}/include
		${PROJECT_SOURCE_DIR}/3rd/assimp/include
		${CMAKE_CURRENT_SOURCE_DIR}/3rd/assimp/include
		DOC "The directory where ASSIMP/types.h resides")
        
    if (CMAKE_SIZEOF_VOID_P EQUAL 8) # x64
		set(PLATFORM x64)
	else() # x86
		set(PLATFORM Win32)
	endif()
        
    if(MSVC12)
		set(ASSIMP_MSVC_VERSION "vc120")
	elseif(MSVC14)	
		set(ASSIMP_MSVC_VERSION "vc140")
	endif(MSVC12)

    FIND_LIBRARY( ASSIMP_LIBRARY
        NAMES assimp-${ASSIMP_MSVC_VERSION}-mt ASSIMP
        PATHS
		${ASSIMP_ROOT_DIR}/lib/${PLATFORM}
		${PROJECT_SOURCE_DIR}/3rd/assimp/lib/${PLATFORM}
        ${CMAKE_CURRENT_SOURCE_DIR}/3rd/assimp/lib/${PLATFORM}
        DOC "The ASSIMP library")
        
ELSE(WIN32)
	FIND_PATH( ASSIMP_INCLUDE_PATH assimp/types.h
		/usr/include
		/usr/local/include
		/sw/include
        /opt/local/include
		${ASSIMP_ROOT_DIR}/include
		DOC "The directory where ASSIMP/types.h resides")

	# Prefer the static library.
	FIND_LIBRARY( ASSIMP_LIBRARY
        NAMES libASSIMP.a ASSIMP libASSIMP.so
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		${ASSIMP_ROOT_DIR}/lib
		DOC "The ASSIMP library")
ENDIF(WIN32)

SET(ASSIMP_FOUND "NO")
IF(ASSIMP_INCLUDE_PATH AND ASSIMP_LIBRARY)
	SET(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})
	SET(ASSIMP_FOUND "YES")
    message(STATUS "Found ASSIMP")
ENDIF(ASSIMP_INCLUDE_PATH AND ASSIMP_LIBRARY)
