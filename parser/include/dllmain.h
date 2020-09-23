#pragma once
/******************************************************
* File: dllmain.cpp
* Date: 2020/09/21
* Author: Zaijun Hao
* Purpose: Use in Matlab to parse binary data saved by VR application
* Reference: https://ww2.mathworks.cn/help/matlab/matlab_external/c-mex-source-file.html
*******************************************************/

#define VRP_EXPORT __declspec(dllexport)
#define VRP_FUNEXP __cdecl

#ifdef __cplusplus
extern "C" {
#endif
		VRP_EXPORT int VRP_FUNEXP getData();

#ifdef __cplusplus
}
#endif
