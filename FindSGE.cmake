# - Try to find SGE
#  
# The following variables are optionally searched for defaults  
#  SGE_ROOT_DIR:            Base directory where all SGE components are found  
#  
# The following are set after configuration is done:  
#  SGE_FOUND  
#  SGE_INCLUDE_DIRS
#  SGE_LIBS
# The OpenGL library already in SEG_LIBS

include(FindPackageHandleStandardArgs)

find_path(SGE_INCLUDE_DIR NAMES sge.h PATHS "${SGE_ROOT_DIR}/include")
find_library(SGE_LIBRARY NAMES sge.lib PATHS "${SGE_ROOT_DIR}/lib")

set(SGE_FOUND TRUE)

find_package(OpenGL REQUIRED)

set(SGE_INCLUDE_DIRS ${SGE_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
set(SGE_LIBS ${SGE_LIBRARY} ${OPENGL_LIBRARIES})

message(STATUS "Found SGE(include: ${SGE_ROOT_DIR}, library: ${SGE_LIBS})") 

mark_as_advanced(SGE_INCLUDE_DIRS SGE_LIBS)
