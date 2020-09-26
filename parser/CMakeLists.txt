cmake_minimum_required(VERSION 3.12)

PROJECT(PARSERLIB LANGUAGES CXX)
aux_source_directory(./source SRC_DIR)
aux_source_directory(./source/utility UTILITY_SRC_DIR)
aux_source_directory(./source/parser PARSER_SOURCE_DIR)
add_library(${PROJECT_NAME} SHARED ${SRC_DIR} ${UTILITY_SRC_DIR} ${PARSER_SOURCE_DIR})
add_library(parser ALIAS ${PROJECT_NAME})
target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )