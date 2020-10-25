#include <fstream>
#include <regex>
#include <unordered_map>
#include "dllmain.h"
#include "utils/utils.h"

using namespace std;
using namespace VrParser;

#define EEGHEADSIZE 12
// A single eeg data block contains 3 long-type header and 350 float-type eeg data
struct EegBlock
{
    long head[3];
    float data[350];
};

DLLEXPORT void DLLFUNEXP vrEegToBrainVision(const char* inFile, const char* outFile)
{
    ofstream ofs(outFile, ios_base::out | ios_base::binary);
    ifstream ifs(inFile, ios_base::in | ios_base::binary);

    if (!ofs.is_open() || !ifs.is_open()) {
        return;
    }
    EegBlock b;
    size_t readSize = sizeof(b);
    size_t writeSize = readSize - EEGHEADSIZE;
    while (ifs && ofs) {
        ifs.read((char*)&b, readSize);
        ofs.write((char*)b.data, writeSize);
    }
    ifs.close();
    ofs.close();
}

DLLEXPORT void DLLFUNEXP vrMarkerToBrainVision(const char* inFile, const char* outFile)
{
    ifstream ifs(inFile, ios_base::in);
    ofstream ofs(outFile);
    regex name("^(\\w+\\b )?(\\w+):\\W?$");
    regex marker("^EEG marker = (\\d+)\\W?$");
    char line[MAX_LINE_LENGTH];
    string markerPos;
    string markerName = "T";
    cmatch m;
    int counter = 1;
    unordered_map<string, int> times;
    ofs << "[Marker Infos]\n";
    while (ifs && ofs) {
        ifs.getline(line, MAX_LINE_LENGTH);
        if (regex_match(line, m, name)) {
            if (m[1].matched) {
                markerName = m[1].str();
            }
            else {
                markerName = m[2].str();
            }
            auto iter = times.find(markerName);
            if (iter == times.end()) {
                times[markerName] = 1;
            }
            else {
                ++iter->second;
            }
        }
        else if (regex_match(line, m, marker)) {
            markerPos = m[1].str();
            ofs << "Mk" << counter << "=Trigger," << markerName
                << "\t" << times[markerName] << ',' << markerPos << ",1,0\n";
            ++counter;
        }
    }
    ifs.close();
    ofs.close();
}

inline string concatPath(const string& p1, const string& p2)
{
    if (p1.back() == '\\' || p1.back() == '/') {
        return p1 + p2;
    }
    return p1 + "\\" + p2;
}

DLLEXPORT void DLLFUNEXP vrEegConvertAllInFolder(const char* inDir, const char* outDir)
{
    //TODO: 各文件名改为和outDir的最后一节相同
    auto& utils = Utils::instance();
    int res = utils->createDirectory(outDir);
    if (res < 0) {
        return;
    }
    vrEegToBrainVision(concatPath(inDir, "eeg.bin").c_str(), concatPath(outDir, "EegData.eeg").c_str());
    vrMarkerToBrainVision(concatPath(inDir, "marker.txt").c_str(), concatPath(outDir, "EegMarker.vmrk").c_str());
    vrEegWriteBrainVisionHeader(concatPath(outDir, "EegHeader.vhdr").c_str());
}

