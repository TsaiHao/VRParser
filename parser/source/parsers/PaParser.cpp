#include <iostream>
#include <fstream>
#include <memory>
#include "PaParser.h"
#include "utils/utils.h"

using namespace std;
using namespace VrParser;

static auto& utils = Utils::instance();

void VrParser::PaParser::parse(const std::string file) {
    string buffer;
    int r = utils->readFileToBuffer(file, buffer);
    if (r < 0) {
        const string msg = "PaParser error: " + file + " does not exists";
        utils->logError(msg);
        return;
    }

    // TODO: optimize memory copy times
    size_t size = buffer.size();
    if (size == 0) {
        return;
    }
    _length = size / 4;
    _floatData = new float[_length];
    copy((char*)(&(buffer[0])), (char*)(&buffer[size-1]), (char*)_floatData);
}

std::vector<float> PaParser::getPositionByColumn(const size_t beg, const size_t end) const {
    return vector<float>();
}

std::vector<float> PaParser::getRotationByColumn(const size_t beg, const size_t end, bool euler) const {
    const size_t left = beg * channels();
    const size_t right = end * channels();
    if (right > length()) {
        return vector<float>();
    }

    if (euler) {
        return utils->quaternionToEuler(_floatData + left, end - beg, 3);
    }
    else {
        return _pickRotation(beg, end);
    }
}

std::vector<float> PaParser::_pickRotation(const size_t beg, const size_t end) const {
    size_t items = end - beg;
    vector<float> rots = vector<float>(items * 4);
    int step = 7;
    for (int i = 0; i < items; ++i) {
        float* col = (beg + i) * step + _floatData;
        copy(col + 3, col + 7, rots.begin() + i * 4);
    }
    return rots;
}
