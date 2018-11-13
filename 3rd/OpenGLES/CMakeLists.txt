cmake_minimum_required (VERSION 2.8)

if(WIN32)

	#set the bin/lib dir
	if (CMAKE_SIZEOF_VOID_P EQUAL 8) # x64
		set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/x64)
		set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64)
	else() # x86
		set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/x86)
		set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/x86)
	endif()

	#import EGL
	add_library(EGL SHARED IMPORTED GLOBAL)
	set_property(TARGET EGL PROPERTY IMPORTED_LOCATION	${BIN_DIR}/libEGL.dll)
	set_property(TARGET EGL PROPERTY IMPORTED_IMPLIB	${LIB_DIR}/libEGL.lib)
	set_property(TARGET EGL PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)

	#import GLESv2
	add_library(GLESv2 SHARED IMPORTED GLOBAL)
	set_property(TARGET GLESv2 PROPERTY IMPORTED_LOCATION	${BIN_DIR}/libGLESv2.dll)
	set_property(TARGET GLESv2 PROPERTY IMPORTED_IMPLIB		${LIB_DIR}/libGLESv2.lib)
	set_property(TARGET GLESv2 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)

	#install the bin dir
	install(DIRECTORY "${BIN_DIR}/"		DESTINATION		.)

else() 

	#TODO: Unix Or Android
	message("Unsupported Unix Or Android")
	
endif()