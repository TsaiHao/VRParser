#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "mex.hpp"
#include "mexAdapter.hpp"

#include "dllmain.h"

using matlab::mex::ArgumentList;
using namespace matlab::data;
using namespace std;
class MexFunction : public matlab::mex::Function {
    shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
    ArrayFactory factory;

public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
        unsigned int size = 0;
        float* data = nullptr;
        TypedArray<float> eeg = factory.createArray<float>({1, 1}, {0});
        TypedArray<int> status = factory.createArray<int>({1, 1}, {0});
        if (inputs.empty()) {
            status[0] = -3;
            outputs[0] = std::move(status);
            outputs[1] = std::move(eeg);
            return;
        }
        CharArray path = inputs[0];

        string inFile = path.toAscii();
        int ret = vrReadAllEegData(inFile.c_str(), &data, &size);
        if (ret != 0) {
            status[0] = -4;
            outputs[0] = std::move(status);
            outputs[1] = std::move(eeg);
            return;
        }

        eeg = factory.createArray<float>({35, size / 35}, data, data + size);
        outputs[1] = std::move(eeg);
        outputs[0] = std::move(status);
    }
};
