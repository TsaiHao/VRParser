#include <fstream>
#include <filesystem>
#include <iostream>
#include "dllmain.h"
#include "utils/utils.h"
#include "VibrationExperiment.h"
#include "parsers/ParserFactory.h"

using namespace std;
namespace fs = std::filesystem;

void VrParser::VibrationExperiment::splitEegByMarkers(const std::string outDir) {
    auto& util = Utils::instance();
    if (_parsers.find("eeg") == _parsers.end()) {
        return;
    }
    if (!util->exists(outDir)) {
        if (util->createDirectory(outDir) < 0) {
            return;
        }
    }

    auto out = fs::path(outDir);
    auto& parser = _parsers["eeg"];
    int i = 0;
    char fmt[] = "eeg_%02d_%s_%02d_%s";
    string buffer(100, '\0');
    for (auto& marker : _markers.Markers()) {
        if (marker.comment().substr(0, 4) == "Void") {
            size_t beg = marker.getCounter("eeg") + 2500;
            size_t end = beg + 20 * 500;
            float* data = nullptr;
            int k = parser->getDataByColumn(&data, beg, end);
            if (k <= 0) {
                continue;
            }
            snprintf(&(buffer[0]), buffer.size(), fmt,
                     subject(), vib().c_str(), trail(), _bias[i++].toString().c_str());
            ofstream ofs(out / buffer);
            if (!ofs) {
                continue;
            }
            ofs.write((char*)data, k * 4);
        }
    }
}

const std::string VrParser::VibrationExperiment::getDataPath() const {
    if (_vib.empty()) {
        return "";
    }
    return _rootPath / std::to_string(_subject) / _vib / std::to_string(_trail);
}

void VrParser::VibrationExperiment::initialize() {
    const string dp = getDataPath();
    if (!dp.empty()) {
        _init(dp);
    }
}

void VrParser::VibrationExperiment::_init(const filesystem::path &dp) {
    for (const auto& entry : fs::directory_iterator(dp)) {
        fs::path p(entry);
        string name = classify(p.filename());
        if (!name.empty()) {
            _parsers[name] = GetParser(name);
            _parsers[name]->parse(p);
        }
    }
    if (fs::exists(fs::path(dp) / "marker.txt")) {
        _markers = MarkerParser(fs::path(dp) / "marker.txt");
        auto& ms = _markers.Markers();
        for (auto iter = ms.begin(); iter < ms.end();) {
            if (iter->comment().substr(0, 4) != "Void") {
                iter = ms.erase(iter);
            }
            else {
                //iter->comment("New Segment");
                ++iter;
            }
        }
    }
    if (fs::exists(fs::path(dp) / "bias.txt")) {
        _parseBias();
    }
}

void VrParser::VibrationExperiment::_parseBias() {
    auto& util = Utils::instance();
    fs::path p = fs::path(getDataPath()) / "bias.txt";
    _bias.clear();

    ifstream ifs(p);
    int x, y;
    while (ifs >> x >> y) {
        _bias.push_back({x, y});
    }
    ifs.close();
}

void VrParser::VibrationExperiment::transcodeForEeglab(const std::string outDir) {
    fs::path root(outDir);
    auto& utils = Utils::instance();
    if (!utils->exists(root)) {
        if (utils->createDirectory(outDir) < 0) {
            return;
        }
    }
    fs::path dataPath = root / "EegData.eeg";
    fs::path markerPath = root / "EegMarker.vmrk";
    fs::path headPath = root / "EegHeader.vhdr";
    writeEeglabData(dataPath);
    writeEeglabHeader(headPath);
    writeEeglabMarker(markerPath);
}

void VrParser::VibrationExperiment::writeEeglabData(const std::string outFile) {
    ofstream ofs(outFile, ios::out | ios::binary);
    if (!ofs) {
        return;
    }
    for (auto& m : _markers.Markers()) {
        size_t beg = m.getCounter("eeg") + 5000;
        size_t end = beg + TRAIL_DURATION;
        float* data = nullptr;
        int k = _parsers["eeg"]->getDataByColumn(&data, beg, end);
        if (k < 0) {
            cerr << "Read data error" << endl;
            return;
        }
        else {
            ofs.write((char*)data, k * 4);
        }
    }
    ofs.close();
}

void VrParser::VibrationExperiment::writeEeglabMarker(const std::string outFile) {
    ofstream ofs(outFile);
    if (!ofs) {
        return;
    }
    ofs << "[Common Infos]\n"
           "DataFile=EegData.eeg" << endl;
    ofs << "[Marker Infos]\n";
    char fmt[] = "Mk%d=New Segment,%s,%d,%d,0\n";
    string buffer(1000, '\0');
    int i = 0;
    for (auto& m : _markers.Markers()) {
        int k = snprintf(&(buffer[0]), buffer.size(), fmt,
                 i + 1, m.comment().c_str(), i * TRAIL_DURATION + 1, TRAIL_DURATION);
        ofs.write(buffer.c_str(), k);
        ++i;
    }
    ofs.close();
}

void VrParser::VibrationExperiment::writeEeglabHeader(const std::string outFile) {
    vrEegWriteBrainVisionHeader(outFile.c_str());
}
