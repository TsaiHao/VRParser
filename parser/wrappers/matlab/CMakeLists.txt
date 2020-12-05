project(matlab)

message(STATUS "matlab library compiling")
set(MEX_SRC mex_wrapper)

add_library(${MEX_NAME} SHARED ${MEX_SRC}.cpp)

add_custom_command(TARGET ${MEX_NAME} PRE_BUILD
        COMMAND mex
        ARGS ${CMAKE_CURRENT_SOURCE_DIR}/${MEX_SRC}.cpp)
if(UNIX)
    message(STATUS "Unix system detected")
    add_custom_command(TARGET ${MEX_NAME} POST_BUILD
        COMMAND cp
        ARGS ${CMAKE_CURRENT_BINARY_DIR}/${MEX_SRC}.mexa64
             ${CMAKE_CURRENT_SOURCE_DIR})
endif(UNIX)