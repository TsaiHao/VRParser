#ifndef VRPARSER_PARSERFACTORY_H
#define VRPARSER_PARSERFACTORY_H
#include <memory>
#include <string>
#include "ParserBase.h"
#include "EegParser.h"
#include "EmgParser.h"
#include "FtParser.h"
#include "PaParser.h"

namespace VrParser {
    std::unique_ptr<ParserBase> GetParser(const std::string name);

}
#endif //VRPARSER_PARSERFACTORY_H
