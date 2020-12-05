project(matlab)

message(STATUS "matlab library compiling")
set(MEX_SRC mex_wrapper)
set(LIB_NAME vrwrapper)
set(MEX_NAME parsermex)

add_library(${LIB_NAME} SHARED ${MEX_SRC}.cpp)

matlab_add_mex(NAME ${MEX_NAME}
        SRC ${MEX_SRC}.cpp
        LINK_TO parser)
if(UNIX)
    message(STATUS "Unix system detected")
    add_custom_command(TARGET ${MEX_NAME} POST_BUILD
            COMMAND cp
            ARGS ${CMAKE_CURRENT_BINARY_DIR}/${MEX_NAME}.mexa64
            ${CMAKE_CURRENT_SOURCE_DIR})
endif(UNIX)