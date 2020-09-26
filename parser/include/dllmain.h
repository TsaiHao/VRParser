#pragma once
/******************************************************
* File: dllmain.cpp
* Date: 2020/09/21
* Author: Zaijun Hao
* Purpose: Use in Matlab to parse binary data saved by VR application
* Reference: https://ww2.mathworks.cn/help/matlab/matlab_external/c-mex-source-file.html
*******************************************************/

#define DLLEXPORT __declspec(dllexport)
#define DLLFUNEXP __cdecl
#define MAX_LINE_LENGTH 1000
#ifdef __cplusplus
extern "C" {
#endif
DLLEXPORT void DLLFUNEXP vrEegToBrainVision(const char* inFile, const char* outFile);
DLLEXPORT void DLLFUNEXP vrMarkerToBrainVision(const char* inFile, const char* outFile);
DLLEXPORT void DLLFUNEXP vrEegWriteBrainVisionHeader(const char* outFile);
DLLEXPORT void DLLFUNEXP vrEegConvertAllInFolder(const char* inDir, const char* outDir);
#ifdef __cplusplus
}
#endif