#include <string>
#include <filesystem>
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
    ifstream ifs(file);
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