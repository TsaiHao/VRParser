#include <unordered_map>
#include "Experiment.h"
#include "parsers/ParserFactory.h"

using namespace VrParser;
using namespace std;
namespace fs = std::filesystem;

unordered_map<string, int> Experiment::Channels =
        unordered_map<string, int> {
                {"eeg", 35},
                {"emg", 16},
                {"ft", 6},
                {"pa", 7}
};

Experiment::Experiment() {

}

const std::string Experiment::classify(const fs::path& p) const {
    auto stem = p.stem();
    auto ext = p.extension();
    if (stem == "eeg") {
        return "eeg";
    }
    else if (stem == "position") {
        return "pa";
    }
    else if (stem == "emg") {
        return "emg";
    }
    else if (stem == "thumb") {
        return "ft";
    }

    return "";
}

