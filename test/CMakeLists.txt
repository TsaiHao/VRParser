cmake_minimum_required(VERSION 3.12)

project(vrtest)
aux_source_directory(./source TEST_SRC_DIR)
add_executable(${PROJECT_NAME} ${TEST_SRC_DIR})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        PUBLIC ${SRC_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../parser/include/)
target_link_libraries(${PROJECT_NAME}
        PUBLIC parser)