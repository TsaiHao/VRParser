#include <string>
#include <filesystem>
#include <fstream>
#include "utils.h"

using namespace std;

int VrParser::Utils::createDirectory(const std::string& file) const 
{
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
    content = string(size, '\0');
    ifs.read(&content[0], size);
    ifs.close();
    return size;
}

std::vector<std::string> VrParser::Utils::readFileLines(const string &file) const {
    ifstream ifs(file);
    vector<string> lines;
    if (!ifs) {
        ifs.close();
        return lines;
    }

    string line;
    while (getline(ifs, line)) {
        lines.push_back(std::move(line));
    }
    ifs.close();
    return lines;
}

