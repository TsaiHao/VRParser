#ifndef VRPARSER_PARSERBASE_H
#define VRPARSER_PARSERBASE_H

#include <string>
#include <memory>
#include "dllmain.h"

namespace VrParser {
    class DLLEXPORT ParserBase {
    public:
        ParserBase():
                _floatData(nullptr),
                _channels(1),
                _length(0),
                _samplingRate(0)
        {}

        virtual ~ParserBase() {
            if (_floatData != nullptr) {
                delete[] _floatData;
            }
        }

        // time is in seconds;
        int getDataByTime(float** data, const float beg, const float end) const {
            if (_floatData == nullptr) {
                return 0;
            }
            size_t left = beg * channels() * samplingRate();
            size_t right = end * channels() * samplingRate();
            if (right >= length()) {
                return -1;
            }
            *data = _floatData + left;
            return right - left;
        }

        int getDataByColumn(float** data, const size_t beg, const size_t end) const {
            if (_floatData == nullptr) {
                return 0;
            }
            size_t left = beg * channels();
            size_t right = end * channels();
            if (right >= length()) {
                return -1;
            }
            *data = _floatData + left;
            return right - left;
        }

        virtual void parse(const std::string file) = 0;

        const float samplingRate() const {
            return _samplingRate;
        }

        const size_t length() const {
            return _length;
        }

        const size_t channels() const {
            return _channels;
        }

    protected:
        float* _floatData;
        float _samplingRate;
        size_t _length;
        size_t _channels;
    };
}
#endif //VRPARSER_PARSERBASE_H
