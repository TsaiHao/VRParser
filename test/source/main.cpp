#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <string.h>
#include <filesystem>
#include "dllmain.h"
#include "parsers/EegParser.h"
#include "Experiment/Experiment.h"
#include "Experiment/VibrationExperiment.h"
using namespace std;
using namespace VrParser;
namespace fs = std::filesystem;
int main()
{
    const char* root = "/home/zaijun/Research/vr/data/";
    const char* path = "/home/zaijun/Research/vr/data/7/off/1";
    //VibrationExperiment exp(root, 7, 1, "on");
    //exp.splitEegByMarkers("/home/zaijun/Research/vr/eeg");
    vrEegConvertAllInFolder(path, "/home/zaijun/Research/vr/temp1");
    return 0;
}