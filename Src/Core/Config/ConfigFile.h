#ifndef __CONFIG_FILE_H
#define __CONFIG_FILE_H

#include <memory>
#include <string>

#include "Core/Config/Settings.h"

namespace Config
{

class ConfigFile
{
public:
	ConfigFile(const std::string& filename, Settings* settings);

	void read();

private:
	void parseLine(const std::string& line);

private:
	std::string filename;
	Settings* settings;
};

} // namespace Config

#endif // __CONFIG_FILE_H
