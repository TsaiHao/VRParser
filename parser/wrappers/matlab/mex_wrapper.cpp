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
        int size = 0;
        const char* path = "/home/zaijun/Research/vr/data/7/on/2/emg.bin";
        float* data = vrEmgReadToArray(path, &size);
        //vector<float> emg(data, data + size);
        TypedArray<float> ret = factory.createArray<float>(
                {1, static_cast<unsigned long>(size)},
                data,
                data + size);
        outputs[0] = std::move(ret);
    }
};
