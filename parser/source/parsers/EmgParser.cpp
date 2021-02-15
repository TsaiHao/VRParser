#include <string>
#include <algorithm>
#include "utils/utils.h"
#include "EmgParser.h"

using namespace std;
using namespace VrParser;

static auto& utils = Utils::instance();

void VrParser::EmgParser::parse(const std::string file) {
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
    _length = size / 4;
    _floatData = new float[_length];
    copy((char*)(&(buffer[0])), (char*)(&buffer[size-1]), (char*)_floatData);
}

void EmgParser::reduceChannel(const int realChannel) {
    if (realChannel >= _channels || realChannel <= 0 || _floatData == nullptr) {
        return;
    }

    const size_t cols = columns();
    float* newBlock = new float[realChannel * cols];

    for (int i = 0; i < cols; ++i) {
        copy(_floatData + i * _channels,
             _floatData + i * _channels + realChannel,
             newBlock + i * realChannel);
    }
    delete[] _floatData;
    _floatData = newBlock;
    _length = _length * realChannel / _channels;
    _channels = realChannel;
}
