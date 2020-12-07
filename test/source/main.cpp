#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string.h>
#include "dllmain.h"
using namespace std;

int main()
{
    //const char* path = "/home/zaijun/Research/vr/data/7/on/1";
    const char* path = "/home/zaijun/Research/vr/data/7/off/1";
    const char* tar = "/home/zaijun/Research/vr/temp";
    float* data = nullptr;
    unsigned int size = 0;
    const string s = string(path) + "/eeg.bin";
    int r = vrReadAllEegData(s.c_str(), &data, &size);
    delete[] data;
    return 0;
}