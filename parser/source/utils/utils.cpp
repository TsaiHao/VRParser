#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>
#include "utils.h"

using namespace std;

int VrParser::Utils::createDirectory(const std::string& file) const 
{
    filesystem::path pt(file);
    if (!filesystem::exists(pt.parent_path())) {
        createDirectory(pt.parent_path().string());
    }
	bool res = filesystem::create_directory(file);
	return res ? 1 : -1;
}

bool VrParser::Utils::exists(const string &p) const {
    return filesystem::exists(p);
}

int VrParser::Utils::readFileToBuffer(const string &file, string& content) const {
    ifstream ifs(file, ios::binary | ios::in);
    if (!ifs) {
        return -1;
    }
    ifs.seekg(0, ios::end);
    int size = ifs.tellg();
    if (size == 0) {
        return 0;
    }

    ifs.seekg(0, ios::beg);
    content.resize(size);
    ifs.read(&content[0], size);
    ifs.close();
    return size;
}

std::vector<std::string> VrParser::Utils::readFileLines(const string &file) const {
    ifstream ifs;
    try {
        ifs.open(file);
    }
    catch (exception& e) {
        return {};
    }
    vector<string> lines;
    if (!ifs) {
        return lines;
    }

    string line;
    while (getline(ifs, line)) {
        lines.push_back(std::move(line));
    }
    ifs.close();
    return lines;
}

std::vector<float> VrParser::Utils::quaternionToEuler(const vector<float> &quats) const noexcept {
    return quaternionToEuler(quats.data(), quats.size() / 4, 0);
}

std::vector<float>
VrParser::Utils::quaternionToEuler(const float *const quats, const size_t items, const size_t padding) const noexcept {
    size_t step = padding + 4;
    if (items < 0) {
        return std::vector<float>();
    }
    float eulers[3];
    vector<float> data(items * 3);
    for (int i = 0; i < items; ++i) {
        const float* const beg = quats + i * step + padding;
        _quatToEulerIntern(beg, eulers);
        copy(eulers, eulers + 3, data.begin() + i * 3);
    }
    return data;
}


void VrParser::Matrix::rightMultiply(float* const right, int rows) const
{
	std::vector<float> temp(row);
	float* dp = right;
	for (int r = 0; r < rows; ++r) {
		for (int i = 0; i < row; ++i) {
			temp[i] = 0;
			for (int j = 0; j < col; ++j) {
				temp[i] += data[i * row + j] * dp[j];
			}
		}
		for (int i = 0; i < row; ++i) {
			dp[i] = temp[i];
		}
        dp += col;
	}
}

void VrParser::Matrix::readFromCSV(std::string const& file, std::string const& delimiter, int beginRow, int endRow)
{
    auto& utils = Utils::instance();
    auto lines = utils->readFileLines(file);
    if (lines.size() < endRow) {
        return;
    }
    row = endRow - beginRow;
    string del(delimiter.size(), '0');
    for (int i = beginRow; i < endRow; ++i) {
        istringstream iss(lines[i]);
        vector<float> temp;
        while (iss) {
            float x;
            iss >> x;
            iss.read(&(del[0]), del.size());
            if (iss) {
                temp.push_back(x);
            }
        }
        if (col == 0) {
            col = temp.size();
            data = vector<float>(col * row);
        }
        copy(temp.begin(), temp.end(), data.begin() + i * col);
    }
}
