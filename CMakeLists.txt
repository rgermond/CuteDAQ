cmake_minimum_required(VERSION 3.5)
project(CUTE_DAQ)

#extra compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11")

#tell the compiler about the headers
include_directories(include)

#get all of th source files
file(GLOB SOURCES "src/*.cpp")

#deal with directories in project structure
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_executable(daq ${SOURCES})

#include the boost library
find_package(Boost 1.64.0 REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(daq ${Boost_LIBRARIES})

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(daq sqlite3)
target_link_libraries(daq pthread)

