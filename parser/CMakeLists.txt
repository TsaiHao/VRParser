cmake_minimum_required(VERSION 3.12)

PROJECT(parserlib LANGUAGES CXX)

set(PARSER_LIB parser)

aux_source_directory(./source SRC_DIR)
aux_source_directory(source/utils UTILITY_SRC_DIR)
aux_source_directory(./source/parsers PARSER_SOURCE_DIR)
aux_source_directory(./source/Experiment EXPERIMENT_DIR)

add_library(${PARSER_LIB} SHARED ${SRC_DIR} ${UTILITY_SRC_DIR} ${PARSER_SOURCE_DIR} ${EXPERIMENT_DIR})
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/source
        )
