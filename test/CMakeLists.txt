cmake_minimum_required(VERSION 3.12)

project(VRPTEST)
aux_source_directory(./source SRC_DIR)
add_executable(${PROJECT_NAME} ${SRC_DIR})
target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        PUBLIC )
target_link_libraries(${PROJECT_NAME}
        parser)