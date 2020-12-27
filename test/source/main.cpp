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
    const char* root = "D:\\Document\\LabWork\\Projects\\vr\\data";
    const char* outDir = "D:\\Document\\LabWork\\Projects\\vr\\converted";

    vector<int> subs{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    vector<string> vibs{ "on", "off" };
    vector<int> tris{ 0, 1, 2 };
    for (auto s : subs) {
        for (auto v : vibs) {
            for (auto t : tris) {
                VibrationExperiment ve(root, s, t, v);
                ve.initialize();
                ve.transcodeForSingleTrial(outDir);
            }
        }
    }

    return 0;
}