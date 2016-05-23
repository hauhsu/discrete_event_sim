cmake_minimum_required(VERSION 2.8.2)
project(MM1QueueSimulator)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(YamlCpp REQUIRED)
find_package( Boost 1.40 COMPONENTS program_options REQUIRED )

include_directories(${yaml_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(MM1QueueSimulator ${sources})
target_link_libraries(MM1QueueSimulator ${YAMLCPP_LIBRARIES} ${Boost_LIBRARIES})

