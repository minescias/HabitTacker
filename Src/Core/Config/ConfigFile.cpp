#include "Core/Config/ConfigFile.h"

#include <fstream>

#include "Core/Exceptions/RuntimeError.h"

namespace Config
{

ConfigFile::ConfigFile(const std::string& filename, Settings* settings)
	: filename(filename)
	, settings(settings)
{
}

void ConfigFile::read()
{
	std::ifstream file(filename);
	std::string line;

	while (getline(file, line)) {
		parseLine(line);
	}
	file.close();
}

void ConfigFile::parseLine(const std::string& line)
{
	if (*line.begin() == '#')
		return;

	auto eqPosition = line.find('=');
	if (eqPosition == std::string::npos)
		throw RuntimeError("Error in config file in line '" + line + "'");

	auto name = line.substr(0, eqPosition);
	auto value = line.substr(eqPosition + 1);

	settings->set(name, value);
}

} // namespace Config
