#ifndef VRPARSER_EEGPARSER_H
#define VRPARSER_EEGPARSER_H

#include "ParserBase.h"

namespace VrParser {

    struct EegBlockHeader {
        int32_t nBlock;
        int32_t nPoint;
        int32_t nMarker;
    };

    struct EegBlock
    {
        int32_t nBlock;
        int32_t nPoint;
        int32_t nMarker;
        float data[350];
        enum {HEADNUM = 3, HEADSIZE = 12,
            DATANUM = 350, DATASIZE = 1400};
    };

    struct EegMarker
    {
        unsigned int nSize;
        unsigned int nPosition;
        unsigned int nPoints;
        int32_t nChannel;
        char sTypeDesc[1000];
    };

    class EegParser : public ParserBase {
    public:
        EegParser() : _capacity(0) {
            _floatData = nullptr;
            _samplingRate = 500;
            _channels = 35;
            _length = 0;
        }

        virtual void parse(const std::string file) override;

    private:
        size_t _capacity;
    };
}
#endif //VRPARSER_EEGPARSER_H
