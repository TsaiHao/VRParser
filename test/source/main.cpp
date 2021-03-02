#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <string.h>
#include <thread>
#include <filesystem>
#include <time.h>
#include "dllmain.h"
#include "parsers/EmgParser.h"
#include "experiment/VibrationExperiment.h"
using namespace std;
using namespace VrParser;
namespace fs = std::filesystem;

string getDir(const string& root, const int sub, const string& vib, const int tri)
{
    fs::path ret = fs::path(root) / to_string(sub) / vib / to_string(tri);
    return ret.string();
}


#if 1
const char* root = "/mnt/d/Document/LabWork/Projects/vr/data";
const char* outDir = "/mnt/d/Document/LabWork/Projects/vr/emg";
#else
const char* root = "D:/Document/LabWork/Projects/vr/data";
const char* outDir = "D:/Document/LabWork/Projects/vr/ft";
#endif

void excuteFun(vector<int> const& subs) {
	vector<string> vibs{ "on", "off" };
	vector<int> tris{ 0, 1, 2 };
	for (int s : subs) {
		for (string& v : vibs) {
			for (int t : tris) {
				string indir = getDir(root, s, v, t);
				string outdir = getDir(outDir, s, v, t);
				VibrationExperiment exp(root, s, t, v);
				exp.initialize({ "emg" });
				exp.splitEmgByMarkers(outDir);
			}
		}
		cout << s << " subject has converted" << endl;
	}
}

int main(int argc, char** argv)
{
	clock_t start = clock();
	vector<int> subs{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    int nThread = 3;
    if (argc > 1) {
        nThread = atoi(argv[1]);
		nThread = nThread > subs.size() ? subs.size() : nThread;
    }
	cout << "using " << (subs.size() % nThread == 0 ? nThread : nThread + 1) << " threading transcoding" << endl;
	vector<thread> threadPool(nThread);
	int nSub = subs.size() / nThread;
	for (int i = 0; i < nThread; ++i) {
		threadPool[i] = thread(excuteFun, vector<int>(subs.begin() + i * nSub,
			subs.begin() + (i + 1) * nSub));
	}
	int res = subs.size() % nThread;
	if (res != 0) {
		threadPool.push_back(thread(excuteFun, vector<int>(subs.end() - res,
			subs.end())));
	}
	for (auto& th : threadPool) {
		th.join();
	}
	float span = float(clock() - start) / CLOCKS_PER_SEC;
	cout.precision(5);
	cout << "totol time: " << span << endl;

    return 0;
}