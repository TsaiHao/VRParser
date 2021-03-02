#ifndef VRPARSER_FTPARSER_H
#define VRPARSER_FTPARSER_H

#include "ParserBase.h"

namespace VrParser {
    class FtParser : public ParserBase {
    public:
        FtParser() : ParserBase(nullptr, 1000, 0, 6)
        { }

        void parse(const std::string file) override;
        
    protected:
        void demean(int meanRows = 100);
    };
}
#endif //VRPARSER_FTPARSER_H
