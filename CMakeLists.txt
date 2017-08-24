cmake_minimum_required(VERSION 2.8)

project(memory_manager)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB sources "src/*.cpp")
file(GLOB headers "include/*.hpp")

include_directories(
  "${CMAKE_SOURCE_DIR}/include"
)
add_library(${CMAKE_PROJECT_NAME} STATIC ${sources} ${headers})

add_subdirectory("./3rdparty/googletest")
add_subdirectory("./test")
