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
    }

    return ptr;
}
