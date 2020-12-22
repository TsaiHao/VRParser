#include <fstream>
#include <regex>
#include <dllmain.h>
#include "MarkerParser.h"
#include "../utils/utils.h"
using namespace std;

void VrParser::MarkerParser::parseFile(const std::string &mfile) {
    _markers.clear();
    _names.clear();
    auto& util = VrParser::Utils::instance();
    auto lines = util->readFileLines(mfile);
    regex name_regex("^(\\w+\\b )?(\\w+):\\W*?$");
    regex marker_regex("^(\\w+) marker = (\\d+)\\W*$");
    Marker marker;

    size_t i = 0;
    while (i < lines.size()) {
        smatch m;
        if (regex_match(lines[i], m, name_regex)) {
            marker.clear();
            marker.comment(m[1].str().empty() ? m[2].str() : m[1].str());
            ++i;
            while (i < lines.size() && regex_match(lines[i], m, marker_regex)) {
                string n = m[1].str();
                std::transform(n.begin(), n.end(), n.begin(),
                               [](unsigned char c) {return std::tolower(c);});
                marker.addCounter(n, atoi(m[2].str().c_str()));
                _names.insert(n);
                ++i;
            }
            _markers.push_back(marker);
        }
        else {
            ++i;
        }
    }
}

VrParser::MarkerParser::MarkerParser(const string &mfile) {
    parseFile(mfile);
}

void VrParser::MarkerParser::removeUncommonMarkers() {
    decltype(_markers) common;
    for (auto& m: _markers) {
        bool com = true;
        for (auto& n: _names) {
            if (!m.hasName(n)) {
                com = false;
                break;
            }
        }
        if (com) {
            common.push_back(m);
        }
    }
    _markers = std::move(common);
}

void VrParser::MarkerParser::generateMatlabClass(const std::string &fname) {
    ofstream ofs(fname);
    if (!ofs) {
        return;
    }

    const string head = "classdef MarkerInfo\n\tproperties\n";
    const string end = "\tend\nend\n";
    ofs << head;
    for (auto& name : _names) {
        ofs << "\t\t" << name << " int32" << endl;
    }
    ofs << "\tend\n\tmethods\n";
    ofs << "\t\tfunction obj = MarkerInfo(";
    for (auto& name : _names) {
        ofs << name << ", ";
    }
    if (!_names.empty()) {
        ofs.seekp(-2, ios::cur);
        ofs << ")\n";
    }
    else {
        ofs << ")\n";
    }
    ofs << "\t\t\tif (nargin == 0)\n\t\t\t\treturn\n\t\t\tend\n";
    char line[1000];
    const char* format = "\t\t\tobj.%s = %s;\n";
    for (auto& name : _names) {
        snprintf(line, 1000, format, name.c_str(), name.c_str());
        ofs << line;
    }

    ofs << "\t\tend\n\tend\nend";
    ofs.close();
}
