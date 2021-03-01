#include "ParserBase.h"
#include "ParserFactory.h"
using namespace std;
using namespace VrParser;

unique_ptr<ParserBase> VrParser::GetParser(const string name)
{
    std::unique_ptr<ParserBase> ptr = nullptr;
    if (name == "eeg") {
        ptr = std::make_unique<EegParser>();
    }
    else if (name == "emg") {
        ptr = std::make_unique<EmgParser>();
    }
    else if (name == "pa") {
        ptr = std::make_unique<PaParser>();
    }
    else if (name == "ft") {
        ptr = std::make_unique<FtParser>();
    }

    return ptr;
}
