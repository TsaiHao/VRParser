#include "parser/ParserBase.h"
#include "parser/inspector.h"
#include "dllmain.h"


VRP_EXPORT int VRP_FUNEXP getData()
{
	ParserBase p;
	return 10;
}

VRP_EXPORT inspector* VRP_FUNEXP getInspector(const std::string& name, const std::string& file)
{
	if (name == "EEG") {
		return new EegInspector(file);
	}
	return nullptr;
}
