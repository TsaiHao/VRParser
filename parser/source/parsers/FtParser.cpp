#include <string>
#include <algorithm>
#include "utils/utils.h"
#include "FtParser.h"

using namespace std;
using namespace VrParser;

static auto& utils = Utils::instance();

void VrParser::FtParser::parse(const std::string file) {
    string buffer;
    if (utils->readFileToBuffer(file, buffer) < 0) {
        string msg = "EmgParser error: read file " + file + "\n";
        utils->logError(msg);
        return;
    }

    size_t size = buffer.size();
    if (size == 0) {
        return;
    }
    _length = size / 8;
    _floatData = new float[_length];

    double* origin = (double*)&(buffer[0]);
    float* target = _floatData;
    for (int i = 0; i < _length; ++i, ++origin, ++target) {
        *target = static_cast<float>(*origin);
    }
}