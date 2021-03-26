#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <numeric>
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
const char* root = "E:\\Haozaijun\\ExperimentData\\Mengjies\\exp2\\data\\";
const char* outDir = "E:\\Haozaijun\\ExperimentData\\Mengjies\\exp2\\eeg\\";
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
				exp.initialize({ "eeg" });
				exp.transcodeForEeglab(outDir);
			}
		}
		cout << s << " subject has converted" << endl;
	}
}

int main(int argc, char** argv)
{
	vector<int> subs(10);
	iota(subs.begin(), subs.end(), 2);
	int lenp = 10000 * 35;
	int len = lenp * subs.size();
	vector<float> ondata(len), ofdata(len);
	vector<float> ondata6(len), ofdata6(len);
	int ns = 0;
	fs::path otp = fs::path(outDir);
	for (int s : subs) {
		string indir = getDir(root, s, "on", 0);
		VibrationExperiment exp_on(root, s, 0, "on");
		VibrationExperiment exp_of(root, s, 0, "off");
		exp_on.initialize({ "eeg" });
		exp_of.initialize({ "eeg" });

		for (int i = 0; i < 9; ++i) {
			auto b = exp_on._bias[i];
			auto m = exp_on._markers.Markers()[i];
			if (b.xbias == 0 && b.ybias == 0) {
				int t = m.getCounter("eeg") - 4000;
				int e = t + 10000;
				float* data = nullptr;
				int k = exp_on._parsers["eeg"]->getDataByColumn(&data, t, e);
				if (k < 0) {
					cerr << "get data error" << endl;
					exit(-1);
				}
				else {
					copy(data, data + lenp, ondata.data() + lenp * ns);
				}
			}
			if (b.xbias == 6 && b.ybias == 0) {
				int t = m.getCounter("eeg") - 4000;
				int e = t + 10000;
				float* data = nullptr;
				int k = exp_on._parsers["eeg"]->getDataByColumn(&data, t, e);
				if (k < 0) {
					cerr << "get data error" << endl;
					exit(-1);
				}
				else {
					copy(data, data + lenp, ondata6.data() + lenp * ns);
				}
			}

			b = exp_of._bias[i];
			m = exp_of._markers.Markers()[i];
			if (b.xbias == 0 && b.ybias == 0) {
				int t = m.getCounter("eeg") - 4000;
				int e = t + 10000;
				float* data = nullptr;
				int k = exp_of._parsers["eeg"]->getDataByColumn(&data, t, e);
				if (k < 0) {
					cerr << "get data error" << endl;
					exit(-1);
				}
				else {
					copy(data, data + lenp, ofdata.data() + lenp * ns);
				}
			}
			if (b.xbias == 6 && b.ybias == 0) {
				int t = m.getCounter("eeg") - 4000;
				int e = t + 10000;
				float* data = nullptr;
				int k = exp_of._parsers["eeg"]->getDataByColumn(&data, t, e);
				if (k < 0) {
					cerr << "get data error" << endl;
					exit(-1);
				}
				else {
					copy(data, data + lenp, ofdata6.data() + lenp * ns);
				}
			}
		}
		ns++;
	}

	ofstream ofs(outDir / fs::path("ondata0.eeg"), ios::binary);
	ofs.write((char*)ondata.data(), ondata.size() * 4);
	ofs.close();
	ofs.open(outDir / fs::path("ondata6.eeg"), ios::binary);
	ofs.write((char*)ondata6.data(), ondata.size() * 4);
	ofs.close();
	ofs.open(outDir / fs::path("ofdata0.eeg"), ios::binary);
	ofs.write((char*)ofdata.data(), ondata.size() * 4);
	ofs.close();
	ofs.open(outDir / fs::path("ofdata6.eeg"), ios::binary);
	ofs.write((char*)ofdata6.data(), ondata.size() * 4);
	ofs.close();
	return 0;
}