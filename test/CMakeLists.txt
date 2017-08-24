project(test_memory_manager)

file(GLOB tests "test_*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")
link_libraries(
  gtest
  memory_manager
)
add_executable(${PROJECT_NAME} ${tests})
