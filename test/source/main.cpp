#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <string.h>
#include <filesystem>
#include "dllmain.h"
#include "parsers/EegParser.h"
#include "experiment/VibrationExperiment.h"
using namespace std;
using namespace VrParser;
namespace fs = std::filesystem;
int main()
{
    const char* root = "/home/zaijun/Research/vr/data/";
    const char* path = "/home/zaijun/Research/vr/data/7/off/1";
    VibrationExperiment exp(root, 7, 1, "on");
    exp.initialize();
    exp.transcodeForEeglab("/home/zaijun/Research/vr/temp2");
    return 0;
}