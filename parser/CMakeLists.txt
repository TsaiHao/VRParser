cmake_minimum_required(VERSION 3.12)

PROJECT(PARSERLIB LANGUAGES CXX)
aux_source_directory(./source SRC_DIR)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
add_library(${PROJECT_NAME} SHARED ${SRC_DIR})
add_library(parser ALIAS ${PROJECT_NAME})
target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )