#ifndef VRPARSER_PAPARSER_H
#define VRPARSER_PAPARSER_H

#include <memory>
#include <vector>
#include "ParserBase.h"

namespace VrParser {
    class PaParser : public ParserBase {
    public:
        PaParser() : ParserBase(nullptr, 90, 0, 7)
        { }

        void parse(const std::string file) override;

        std::vector<float> getPositionByColumn(const size_t beg, const size_t end) const;
        std::vector<float> getRotationByColumn(const size_t beg, const size_t end, bool euler = true) const;

    private:
        std::vector<float> _pickRotation(const size_t beg, const size_t end) const;
        std::vector<float> _pickPosition(const size_t beg, const size_t end) const;
    };
}
#endif //VRPARSER_PAPARSER_H
