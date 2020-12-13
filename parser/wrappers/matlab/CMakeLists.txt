project(matlab)

message(STATUS "matlab library compiling")
set(MEX_SRC mex_wrapper)
set(LIB_NAME vrwrapper)
set(MEX_NAME parsermex)

aux_source_directory(functions FUNCTIONS_DIR)
add_library(${LIB_NAME} SHARED ${MEX_SRC}.cpp ${FUNCTIONS_DIR})
