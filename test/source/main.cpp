#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <string.h>
#include "dllmain.h"
#include "utils/MarkerParser.h"

using namespace std;

int main()
{
    const char* path = "/home/zaijun/Research/vr/data/7/on/1/marker.txt";
    const char* eeg = "/home/zaijun/Research/vr/data/Xianglian/4/D2/0/Evaluation1/";

    vrEegConvertAllInFolder(eeg, "/home/zaijun/Research/vr/temp");

    return 0;
}