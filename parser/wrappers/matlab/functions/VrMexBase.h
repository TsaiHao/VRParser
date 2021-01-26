#ifndef VRPARSER_VRMEXBASE_H
#define VRPARSER_VRMEXBASE_H
#include <string>
#include <vector>
#include <memory>
#include "mex.hpp"
#include "mexAdapter.hpp"

using matlab::mex::ArgumentList;
using namespace matlab::data;

class MexBase : public matlab::mex::Function {
protected:
    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
    ArrayFactory factory;

    std::string getPwd() {
        auto pwd = matlabPtr->feval("pwd", 1, std::vector<Array>());
        return CharArray(pwd[0]).toAscii();
    }

    matlab::data::String getCommandFromString(const std::string& str) const {
        return matlab::engine::convertUTF8StringToUTF16String(str);
    }

public:
    virtual int checkArguments(ArgumentList& outputs, ArgumentList& inputs) = 0;
    virtual void logError(const std::string& msg) {
        matlabPtr->feval(u"error", 0,
                         std::vector<Array>({ factory.createScalar(msg.c_str()) }));
    }
    virtual void logMessage(const std::string& msg) {
        matlabPtr->feval(u"disp", 0,
                         std::vector<Array>({ factory.createScalar(msg.c_str()) }));
    }
};
#endif //VRPARSER_VRMEXBASE_H
