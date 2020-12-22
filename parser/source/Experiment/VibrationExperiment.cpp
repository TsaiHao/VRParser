#include <fstream>
#include <filesystem>
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
