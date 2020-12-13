#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <string.h>
#include "dllmain.h"
#include "utils/MarkerParser.h"

using namespace std;

int main()
{
    const char* path = "/home/zaijun/Research/vr/data/7/on/1/marker.txt";

    VrParser::MarkerParser parser(path);
    parser.removeUncommonMarkers();
    cout << parser.Markers().size() << endl;

    return 0;
}