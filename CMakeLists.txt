cmake_minimum_required(VERSION 3.12)

project(VRPARSER LANGUAGES CXX)
add_subdirectory(parser)
add_subdirectory(test)

aux_source_directory(${PROJECT_SOURCE_DIR}/test/source TEST_DIR)
add_executable(vrtest ${TEST_DIR})
target_link_libraries(vrtest parser)