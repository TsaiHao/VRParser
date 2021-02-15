#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <string.h>
#include <filesystem>
#include "dllmain.h"
#include "parsers/EmgParser.h"
#include "experiment/VibrationExperiment.h"
using namespace std;
using namespace VrParser;
namespace fs = std::filesystem;

string getDir(const string& root, const int sub, const string& vib, const int tri)
{
    fs::path ret = fs::path(root) / to_string(sub) / vib / to_string(tri);
    return ret.string();
}

int main()
{
    const char* root = "/home/zaijun/Research/vr/data";
    const char* outDir = "/home/zaijun/Research/vr/emg";

    vector<int> subs{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    vector<string> vibs{ "on", "off" };
    vector<int> tris{ 0, 1, 2 };
    for (int s : subs) {
        for (string& v : vibs) {
            for (int t : tris) {
                string indir = getDir(root, s, v, t);
                string outdir = getDir(outDir, s, v, t);
                VibrationExperiment exp(root, s, t, v);
                exp.initialize({"emg"});
                exp.splitEmgByMarkers(outDir);
            }
        }
        cout << s << " subject has converted" << endl;
    }
    return 0;
}