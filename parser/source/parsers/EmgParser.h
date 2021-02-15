#ifndef VRPARSER_EMGPARSER_H
#define VRPARSER_EMGPARSER_H

#include "ParserBase.h"

namespace VrParser {
    class EmgParser : public ParserBase {
    public:
        EmgParser() : ParserBase(nullptr, 2000, 0, 16)
         { }

        void parse(const std::string file) override;
        void reduceChannel(const int readChannel);
    };
}

#endif //VRPARSER_EMGPARSER_H
