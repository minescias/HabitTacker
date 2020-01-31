#include "Core/Config/ConfigFile.h"

#include <fstream>

#include "nlohmann/json.hpp"

#include "Core/Logger/Log.h"
#include "Core/Exceptions/RuntimeError.h"

namespace Config
{
using json = nlohmann::json;

ConfigFile::ConfigFile(const std::string& filename, Settings* settings)
	: filename(filename), settings(settings)
{
}

void ConfigFile::read()
{
	log("Opening config file in " + filename);
	std::ifstream ifs(filename);
	auto configFile = json::parse(ifs);

	auto availiableSettings = settings->getAllSettings();
	for (const auto& [name, defaultValue] : availiableSettings)
	{
		auto value = configFile.find(name);
		if (value != configFile.end())
			settings->set(name, *value);
	}
}

} // namespace Config
