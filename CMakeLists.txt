cmake_minimum_required(VERSION 3.0.0)
project(ObjectSerialization VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

add_library(Base64 STATIC ./src/Base64.cpp)
add_library(tinyxml2 STATIC ./src/tinyxml2.cpp)
add_library(Bin_Ser STATIC ./src/Bin_Ser.cpp)
add_library(XML_Ser STATIC ./src/XML_Ser.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
add_executable(test ./src/test.cpp)
target_link_libraries(test Bin_Ser XML_Ser Base64 tinyxml2)