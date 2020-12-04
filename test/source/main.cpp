#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include "dllmain.h"
using namespace std;

int main()
{
    ofstream ofs("emg", ios::binary | ios::out);
    vector<float> v{1.2, 1.3, 1.5};
    for (auto i : v) {
        ofs.write((char*)(&i), sizeof(float));
    }
    ofs.close();
    float* data = vrEmgReadToArray("emg");
    for(int i = 0; i < 3; ++i) {
        cout << data[i] << '\t';
    }
    delete[] data;
    return 0;
}