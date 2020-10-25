cmake_minimum_required(VERSION 3.12)

PROJECT(parserlib LANGUAGES CXX)

aux_source_directory(./source SRC_DIR)
aux_source_directory(source/utils UTILITY_SRC_DIR)
aux_source_directory(./source/parser PARSER_SOURCE_DIR)

add_library(${PROJECT_NAME} SHARED ${SRC_DIR} ${UTILITY_SRC_DIR})
add_library(parser ALIAS ${PROJECT_NAME})
target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    $<TARGET_FILE:parserlib> ${PROJECT_SOURCE_DIR}/wrappers/matlab/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${PROJECT_SOURCE_DIR}/include/dllmain.h ${PROJECT_SOURCE_DIR}/wrappers/matlab/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    $<TARGET_FILE:parserlib> ${PROJECT_SOURCE_DIR}/wrappers/python/    
    )
