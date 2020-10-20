#include <iostream>
#include <functional>
#include "dllmain.h"
using namespace std;

int main()
{
    cout << "begin" << endl;
    auto f = bind(vrEegConvertAllInFolder, placeholders::_1, placeholders::_2);
    const char* indir = "E:\\Haozaijun\\ExperimentData\\Mengjies\\exp2\\data\\1\\off\\1";
    const char* outdir = ".\\test";
    f(indir, outdir);
    return 0;
}