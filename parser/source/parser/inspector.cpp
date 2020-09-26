//
// Created by zaijun on 2020/9/23.
//

#include "inspector.h"
using namespace std;

#ifdef min
#undef min
#endif

float* EegInspector::getNextSample(size_t& numOfSmp)
{
	if (_counter >= 10) {
		_counter = 0;
		_ifs.read(_buffer, _bSize);
	}
	float* ret = (_ifs ? _b.data[_counter] : nullptr);
	numOfSmp = getChannels();
	++_counter;
	return ret;
}

float* EegInspector::getNextSamples(size_t samples, size_t& numOfSmp)
{
	return nullptr;
}

void EegInspector::translateToBrainVision(const string& dstName)
{
	ofstream ofs(dstName, ios_base::out | ios_base::binary);
	if (!ofs.is_open()) {
		return;
	}
	vector<float> data = parseAllData();
	ofs.write((char*)data.data(), data.size() * 4);
	ofs.close();
}

vector<float> EegInspector::parseAllData()
{
	int samples = 35 * 500 * 60 * 10;	// about 40MB memory
	int bound = samples / 10;
	vector<float> data;
	data.resize(samples);
	int blocks = 0;
	while (_ifs) {
		_ifs.seekg(12, ios_base::cur);
		if (_ifs) {
			_ifs.read((char*)data.data() + blocks * BlockSize, BlockSize);
		}
		blocks++;
		if (blocks > bound) {
			data.resize(2 * samples);
			samples *= 2;
			bound *= 2;
		}
	}
	data.resize(blocks * BlockSize);
	return data;
}

void EegInspector::_getNewBlock()
{
	_counter = 0;
	_ifs.read(_buffer, _bSize);
}
