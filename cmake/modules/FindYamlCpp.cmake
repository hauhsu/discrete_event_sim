# Locate yaml-cpp
#
# This module defines
#  YAMLCPP_FOUND, if false, do not try to link to yaml-cpp
#  YAMLCPP_LIBRARY, where to find yaml-cpp
#  YAMLCPP_INCLUDE_DIR, where to find yaml.h
#
# By default, the dynamic libraries of yaml-cpp will be found. To find the static ones instead,
# you must set the YAMLCPP_STATIC_LIBRARY variable to TRUE before calling find_package(YamlCpp ...).
#
# If yaml-cpp is not installed in a standard path, you can use the YAMLCPP_DIR CMake variable
# or environment variable YAMLCPP_DIR to tell CMake where yaml-cpp is.

# attempt to find static library first if this is set
if(YAMLCPP_DYNAMIC_LIBRARY)
	message("Searching dynamic yaml-cpp lib") 
    set(YAMLCPP_LIB libyaml-cpp.so)
else()
	message("Searching static yaml-cpp lib") 
    set(YAMLCPP_LIB libyaml-cpp.a)
endif()


find_package(Boost QUIET REQUIRED)
set(YAMLCPP_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
set(YAMLCPP_LIBRARIES ${Boost_LIBRARIES})

# find the yaml-cpp include directory
find_path(YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
	PATH_SUFFIXES include
	PATHS
	~/Library/Frameworks/yaml-cpp/include/
	/Library/Frameworks/yaml-cpp/include/
	/usr/local/include/
	/usr/include/
	/sw/yaml-cpp/         # Fink
	/opt/local/yaml-cpp/  # DarwinPorts
	/opt/csw/yaml-cpp/    # Blastwave
	/opt/yaml-cpp/
	${YAMLCPP_DIR}/include/ 
	${YAMLCPP_DIR}/include/yaml-cpp
	$ENV{YAMLCPP_DIR}/include/ 
	$ENV{YAMLCPP_DIR}/include/yaml-cpp
	)

# find the yaml-cpp library
message ("${YAMLCPP_LIB}")
find_library(YAMLCPP_LIBRARY
	NAMES ${YAMLCPP_LIB} yaml-cpp
	PATH_SUFFIXES lib64 lib
	PATHS ~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt
	${YAMLCPP_DIR}/lib
	$ENV{YAMLCPP_DIR}/lib
	)

set(YAMLCPP_LIBRARIES ${YAMLCPP_LIBRARIES} ${YAMLCPP_LIBRARY})
set(YAMLCPP_INCLUDE_DIRS ${YAMLCPP_INCLUDE_DIRS} ${YAMLCPP_INCLUDE_DIR})

# handle the QUIETLY and REQUIRED arguments and set YAMLCPP_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(YAMLCPP DEFAULT_MSG YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY)
mark_as_advanced(YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY)
