cmake_minimum_required(VERSION 2.8)
include(CMakeDependentOption)
set(TARGET sge)

set(SGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

set(SGE_SOURCE_LIST)
set(SGE_LINK_LIBS)


###########################################################
# options
#----------------------------------------------------------
if(WIN32)
    option(USE_DIRECTX "use DirectX12 render or OpenGL render" OFF)
else()
    set(USE_DIRECTX OFF)
endif()

if(USE_DIRECTX)
    # //TODO: use DirectX
else()
    # use OpenGL
    set(USE_DIRECTX OFF)
    set(USE_OPENGL ON)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    list(APPEND SGE_LINK_LIBS ${OPENGL_LIBRARIES})
    find_package(GLFW3)
endif()
option(EXPORT_ASSET "export asset module" ON)
option(EXPORT_DEVICE "export device module" ON)
cmake_dependent_option(USE_GLFW3 "use glfw3 for device module" ON "EXPORT_DEVICE;GLFW3_FOUND;" OFF)
option(EXPORT_GRAPHICS "export graphics module" ON)
###########################################################


###########################################################
# export core module
#----------------------------------------------------------
file(GLOB_RECURSE SGE_SRC_CORE "${SGE_SOURCE_DIR}/core/*.c" "${SGE_SOURCE_DIR}/core/*.cpp")
list(APPEND SGE_SOURCE_LIST ${SGE_SRC_CORE})
install(DIRECTORY ${SGE_INCLUDE_DIR}/core DESTINATION include)
message("add core module: ${SGE_SRC_CORE}")
###########################################################


###########################################################
# export asset module
#----------------------------------------------------------
if(EXPORT_ASSET)
    if(WIN32)
        file(GLOB_RECURSE SGE_SRC_ASSET "${SGE_SOURCE_DIR}/asset/win32/*.c" "${SGE_SOURCE_DIR}/asset/win32/*.cpp")
    else()
        # //TODO: Add other platform asset module implements
    endif(WIN32)
    list(APPEND SGE_SOURCE_LIST ${SGE_SRC_ASSET})
    install(DIRECTORY ${SGE_INCLUDE_DIR}/asset DESTINATION include)
    message("add asset module: ${SGE_SRC_ASSET}")
endif()
###########################################################


###########################################################
# export input module
#----------------------------------------------------------
if(EXPORT_INPUT)
    file(GLOB_RECURSE SGE_SRC_INPUT "${SGE_SOURCE_DIR}/input/*.c" "${SGE_SOURCE_DIR}/input/*.cpp")
    list(APPEND SGE_SOURCE_LIST ${SGE_SRC_INPUT})
    install(DIRECTORY ${SGE_INCLUDE_DIR}/input DESTINATION include)
    message("add input module: ${SGE_SRC_INPUT}")
endif()
###########################################################


###########################################################
# export device module
#----------------------------------------------------------
if(EXPORT_DEVICE)
    if(USE_GLFW3)
        include_directories(${GLFW3_INCLUDE_PATH})
        list(APPEND SGE_LINK_LIBS ${GLFW3_LIBRARY})
        file(GLOB_RECURSE SGE_SRC_DEVICE "${SGE_SOURCE_DIR}/device/glfw3/*.c" "${SGE_SOURCE_DIR}/device/glfw3/*.cpp")
    else()
        # //TODO: Add other platform device module implements
    endif()
    list(APPEND SGE_SOURCE_LIST ${SGE_SRC_DEVICE})
    install(DIRECTORY ${SGE_INCLUDE_DIR}/device DESTINATION include)
    message("add device module: ${SGE_SRC_DEVICE}")
endif()
###########################################################


###########################################################
# export graphics module
#----------------------------------------------------------
if(EXPORT_GRAPHICS)
    file(GLOB SGE_SRC_GRAPHICS "${SGE_SOURCE_DIR}/graphics/*.c" "${SGE_SOURCE_DIR}/graphics/*.cpp")
    if(USE_OPENGL)
        file(GLOB_RECURSE SGE_SRC_GRAPHICS_OPENGL "${SGE_SOURCE_DIR}/graphics/opengl/*.c" "${SGE_SOURCE_DIR}/graphics/opengl/*.cpp")
        list(APPEND SGE_SRC_GRAPHICS ${SGE_SRC_GRAPHICS_OPENGL})
    else()
        # //TODO: Add DirectX graphics module implements
    endif()
    list(APPEND SGE_SOURCE_LIST ${SGE_SRC_GRAPHICS})
    install(DIRECTORY ${SGE_INCLUDE_DIR}/graphics DESTINATION include)
    message("add graphics module: ${SGE_SRC_GRAPHICS}")
endif()
###########################################################



###########################################################
# add target
#----------------------------------------------------------
message("link libraries: ${SGE_LINK_LIBS}")
add_library(${TARGET} SHARED ${SGE_SOURCE_LIST})
target_link_libraries(${TARGET} ${SGE_LINK_LIBS})
target_include_directories(${TARGET} PUBLIC ${SGE_INCLUDE_DIR})
target_include_directories(${TARGET} PRIVATE ${SGE_SOURCE_DIR})
###########################################################


###########################################################
# install target
#----------------------------------------------------------
install(TARGETS ${TARGET}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib)
###########################################################

