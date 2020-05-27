cmake_minimum_required(VERSION 3.0.0)
project(ObjectSerialization VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

add_library(Bin_Ser SHARED ./src/Bin_Ser.cpp)
add_library(XML_Ser SHARED ./src/XML_Ser.cpp ./src/tinyxml2.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
add_executable(test ./src/test.cpp)
target_link_libraries(test Bin_Ser XML_Ser)