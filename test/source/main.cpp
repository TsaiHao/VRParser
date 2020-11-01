#include <iostream>
#include <functional>
#include "dllmain.h"
using namespace std;

int main()
{
    cout << "begin" << endl;
    auto f = bind(vrEegConvertAllInFolder, placeholders::_1, placeholders::_2);
    return 0;
}