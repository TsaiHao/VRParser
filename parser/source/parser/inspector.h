//
// Created by zaijun on 2020/9/23.
//

#ifndef VRPARSER_INSPECTOR_H
#define VRPARSER_INSPECTOR_H

#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include "dllmain.h"

// inspector base class
class inspector {
public:
	typedef void(*deleter)(float*&);
	inspector(const std::string& fileName) :
		_ifs(std::ifstream(fileName, std::ios::in | std::ios::binary)),
		_file(fileName)
	{
		if (!_ifs.is_open()) {
			throw std::exception("Error: File is not opened");
		}
	}
	virtual ~inspector() {}
	
	virtual inline float* getNextSample(size_t& numOfSmp) = 0;
	virtual float* getNextSamples(size_t samples, size_t& numOfSmp) = 0;
	virtual std::vector<float> parseAllData() = 0;
	virtual size_t getChannels() const = 0;
protected:
	std::string _file;
	std::ifstream _ifs;
};

class  EegInspector: public inspector {
	enum {HeadSize = 12, SampleSize = 140, BlockSize = 1400};
	
public:
	struct block
	{
		long head[3];
		float data[10][35];
	};

	explicit EegInspector(const std::string& fileName) :
		inspector(fileName), _counter(10)
	{
		_buffer = (char*)&_b;
		_bSize = sizeof(_b);
	}

	~EegInspector() override {
	}
	
	inline float* getNextSample(size_t& numOfSmp) override;
	float* getNextSamples(size_t samples, size_t& numOfSmp) override;
	void translateToBrainVision(const std::string& dstName);
	std::vector<float> parseAllData() override;
	size_t getChannels() const override {
		return 35;
	}

private:
	inline void _getNewBlock();
	
	block _b;
	char* _buffer;
	int _counter;
	size_t _bSize;
};


#endif //VRPARSER_INSPECTOR_H
