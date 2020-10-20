#include <string>
#include <filesystem>
#include "utils/utils.h"

using namespace std;

int VrParser::Utils::createDirectory(const std::string& file) const 
{
	bool res = filesystem::create_directory(file);
	return res ? 1 : -1;
}
