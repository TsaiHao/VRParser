#ifndef VRPARSER_VIBRATIONEXPERIMENT_H
#define VRPARSER_VIBRATIONEXPERIMENT_H
#include "Experiment.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include "dllmain.h"
#include "utils/utils.h"

#include "parsers/ParserFactory.h"
#define TRAIL_DURATION (10000)
using namespace std;
namespace fs = std::filesystem;

namespace VrParser {
    class DLLEXPORT VibrationExperiment: public Experiment {
    public:
        VibrationExperiment(const std::string& root, const int s, const int t, const std::string& v) :
            Experiment(root, s, t),
            _vib(v)
        {}

        const std::string getDataPath() const override {
            if (_vib.empty()) {
                return "";
            }
            return (_rootPath / std::to_string(_subject) / _vib / std::to_string(_trail)).string();
        }
        void initialize(const std::set<std::string>& parserList) override {
            const std::string dp = getDataPath();
            if (!dp.empty()) {
                _init(dp, parserList);
            }
        }

        void splitEegByMarkers(const std::string outDir, bool addHeader);
        void splitPaByMarkers(const std::string& outDir);

        // Eeglab related
        void transcodeForEeglab(const std::string outDir);
        void writeEeglabData(const std::string outFile);
        void writeEeglabMarker(const std::string outFile);
        void writeEeglabHeader(const std::string outFile);

        // FieldTrip related
        void transcodeForFiledTrip(const std::string& outDir);
        void writeFtData(const std::string& outFile);
        void writeFtMarker(const std::string& outFile);
        void writeFtHeader(const std::string &outFile, const std::string &dataName,
                           const std::string &markerName);

        // Single trail
        void transcodeForSingleTrial(const std::string& outDir);
        void writeSingleData(const std::string& outDir);
        void writeSingleHeader(const std::string& outFile, const std::string& dataFile);

        std::string& vib() {
            return _vib;
        }
        const std::vector<Bias>& bias() {
            return _bias;
        }

    private:
        std::string _vib;
        std::vector<Bias> _bias;
        std::vector<MarkerParser::Marker> _visualMarkers;
        void _init(const std::filesystem::path& dp, const std::set<std::string>& parserList);
        void _parseBias();
    };
}

#endif //VRPARSER_VIBRATIONEXPERIMENT_H
