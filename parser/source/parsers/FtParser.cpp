#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include "utils/utils.h"
#include "FtParser.h"

using namespace std;
using namespace VrParser;
using filesystem::path;
static auto& utils = Utils::instance();

void VrParser::FtParser::parse(const std::string file) {
    string buffer;
    if (utils->readFileToBuffer(file, buffer) < 0) {
        string msg = "FtParser error: read file " + file + "\n";
        utils->logError(msg);
        return;
    }

    size_t size = buffer.size();
    if (size == 0) {
        return;
    }
    _length = size / 8;
    _floatData = new float[_length];

    double* origin = (double*)&(buffer[0]);
    float* target = _floatData;
    for (int i = 0; i < _length; ++i, ++origin, ++target) {
        *target = static_cast<float>(*origin);
    }
    demean(500);
    vector<float> mat = {
		0.040570000,-0.057120000,-0.178230000,-6.681470000,0.341790000,6.529700000,
		0.423830000,8.053030000,-0.117100000,-3.895640000,-0.182010000,-3.713230000,
		7.508050000,-0.027770000,7.566870000,-0.440750000,7.465600000,0.016450000,
		3.661070000,49.139010000,42.167650000,-25.952070000,-42.212620000,-22.893820000,
		- 48.508730000,0.588890000,26.056390000,39.434020000,22.071830000,-39.939650000,
		1.876810000,30.009050000,0.427740000,29.638070000,1.760180000,27.627730000
    };
    Matrix m(6, 6, mat);
    //m.readFromCSV("ftmatrix.txt", ",", 0, 6);
    m.rightMultiply(_floatData, columns());
}

void FtParser::demean(int meanRows /*= 100*/)
{
    if (_floatData == nullptr || columns() < meanRows) {
        return;
    }
    
    vector<float> mean(channels(), 0);
    for (int i = 0; i < meanRows; ++i) {
        for (int j = 0; j < channels(); ++j) {
            mean[j] += _floatData[i * channels() + j];
        }
    }
    for_each(mean.begin(), mean.end(),
        [meanRows](float& x) { x /= meanRows; });
    for (int i = 0; i < columns(); ++i) {
        for (int j = 0; j < channels(); ++j) {
            _floatData[i * channels() + j] -= mean[j];
        }
    }
}
