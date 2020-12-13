#include <vector>
#include <string>

#include "mex.hpp"
#include "mexAdapter.hpp"

#include "utils/MarkerParser.h"
#include "VrMexBase.h"
#define MAXBUFFERSIZE (1000)

using matlab::mex::ArgumentList;
using namespace matlab::data;
using namespace std;

class MexFunction : public MexBase{
public:
    void operator()(ArgumentList outputs, ArgumentList inputs) {
        if (checkArguments(outputs, inputs) < 0) {
            return;
        }
        CharArray input(inputs[0]);
        string file = input.toAscii();
        VrParser::MarkerParser parser(file);
        parser.removeUncommonMarkers();
        string pwd = getPwd();
        string clsFile = pwd + "/MarkerInfo.m";
        parser.generateMatlabClass(clsFile);

        auto& markers = parser.Markers();
        auto& names = parser.Names();
        logMessage(to_string(markers.size()) + " markers parserd");
        char declareFormat[] = "m(%d) = MarkerInfo()";
        char valueFormat[] = "m(%d).%s = %d;";
        string declareBuffer(MAXBUFFERSIZE, '\0');
        string valueBuffer(MAXBUFFERSIZE, '\0');
        for (int i = 0; i < markers.size(); ++i) {
            snprintf(&(declareBuffer[0]), MAXBUFFERSIZE, declareFormat, i + 1);
            matlabPtr->eval(getCommandFromString(declareBuffer));
            for (auto& name : names) {
                int p = -1;
                if (markers[i].hasName(name)) {
                    p = markers[i].getCounter(name);
                }
                snprintf(&(valueBuffer[0]), MAXBUFFERSIZE, valueFormat, i + 1, name.c_str(), p);
                matlabPtr->eval(getCommandFromString(valueBuffer));
            }
        }
    }

    int checkArguments(ArgumentList& outputs, ArgumentList& inputs) override {
        if (inputs.size() != 1
        || (inputs[0].getType() != ArrayType::MATLAB_STRING
        && inputs[0].getType() != ArrayType::CHAR)) {
            logError("inputs must be 1 char array of marker file name");
            return -1;
        }
        return 0;
    }
};