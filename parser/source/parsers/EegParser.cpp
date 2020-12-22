#include <fstream>
#include "EegParser.h"

using namespace std;

void VrParser::EegParser::parse(const std::string file) {
    ifstream ifs(file, ios::in | ios::binary);
    if (!ifs) {
        return;
    }
    ifs.seekg(0, ios::end);
    size_t bytes = ifs.tellg();
    ifs.seekg(0, ios::beg);
    size_t floats = bytes / 4;
    if (_capacity >= floats && _floatData != nullptr) {
        // do not realloc memory
    }
    else {
        delete[] _floatData;
        _floatData = new float[floats];
        _capacity = floats;
    }

    EegBlock block;
    EegMarker marker;
    EegBlockHeader head;
    char* p = (char*)_floatData;
    while (ifs) {
        ifs.read((char*)&head, EegBlock::HEADSIZE);
        size_t blockSize = head.nPoint * _channels * 4;
        ifs.read((char*)p, blockSize);
        p += blockSize;

        if (head.nMarker > 0) {
            for (int i = 0; i < head.nMarker && ifs; ++i) {
                ifs.read((char*)(&marker.nSize), 4);
                ifs.seekg(marker.nSize - 4, ios::cur);
            }
        }
    }
    _length = (float*)p - _floatData;
}
