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
option(EXPORT_ASSET "export asset module" ON)
option(EXPORT_INPUT "export input module" ON)
option(EXPORT_DEVICE "export device module" ON)
find_package(GLFW3)
if (GLFW3_FOUND)
    cmake_dependent_option(USE_GLFW3 "use glfw3 for device module" ON "EXPORT_DEVICE;NOT USE_DIRECT" OFF)
endif()
###########################################################



###########################################################
# export core module
#----------------------------------------------------------
file(GLOB_RECURSE SGE_SRC_CORE "${SGE_SOURCE_DIR}/core/*.c" "${SGE_SOURCE_DIR}/core/*.cpp")
list(APPEND SGE_SOURCE_LIST ${SGE_SRC_CORE})
install(DIRECTORY ${SGE_INCLUDE_DIR}/core DESTINATION include)
message("add core module")
###########################################################


###########################################################
# export asset module
#----------------------------------------------------------
if(EXPORT_ASSET)
    if(WIN32)
        file(GLOB_RECURSE SGE_SRC_ASSET "${SGE_SOURCE_DIR}/asset/win32/*.c" "${SGE_SOURCE_DIR}/asset/win32/*.cpp")
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
        file(GLOB_RECURSE SGE_SRC_DEVICE_GLFW3 "${SGE_SOURCE_DIR}/device/glfw3/*.c" "${SGE_SOURCE_DIR}/device/glfw3/*.cpp")
    endif()
    list(APPEND SGE_SOURCE_LIST ${SGE_SRC_DEVICE_GLFW3})
    install(DIRECTORY ${SGE_INCLUDE_DIR}/device DESTINATION include)
    message("add device module: ${SGE_SRC_DEVICE_GLFW3}")
endif()
###########################################################



###########################################################
# add target
#----------------------------------------------------------
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

