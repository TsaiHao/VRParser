cmake_minimum_required(VERSION 3.12)

PROJECT(PARSERLIB LANGUAGES CXX)
set(BOOST_PATH "D:/boost_1_74_0")
set(BOOST_INCLUDEDIR ${BOOST_PATH})
set(BOOST_LIBRARY_DIR ${BOOST_PATH}/stage/lib)
set(BOOST_ROOT ${BOOST_PATH}/boost)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.71.0 COMPONENTS filesystem)
aux_source_directory(./source SRC_DIR)
aux_source_directory(./source/utility UTILITY_SRC_DIR)
aux_source_directory(./source/parser PARSER_SOURCE_DIR)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_library(${PROJECT_NAME} SHARED ${SRC_DIR} ${UTILITY_SRC_DIR})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
add_library(parser ALIAS ${PROJECT_NAME})
target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)