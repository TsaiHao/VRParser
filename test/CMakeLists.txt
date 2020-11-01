cmake_minimum_required(VERSION 3.12)

project(vrtestsub)
aux_source_directory(./source TEST_SRC_DIR)

include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        PUBLIC ${SRC_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../parser/include/)