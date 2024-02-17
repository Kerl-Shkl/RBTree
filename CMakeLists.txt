cmake_minimum_required(VERSION 3.22)

project(RedBlackTree VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB HEADER_FILES include/*.h)

add_library(RBTree ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(RBTree PUBLIC include)

add_subdirectory(tests)
