#include <iostream>
#include "parser/ParserBase.h"
#include "parser/inspector.h"

int main()
{
	EegInspector ins("E:\\Haozaijun\\ExperimentData\\1\\eeg.bin");
	ins.translateToBrainVision("E:\\Haozaijun\\test.eeg");
}