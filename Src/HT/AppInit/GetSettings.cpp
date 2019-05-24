#include "HT/AppInit/GetSettings.h"

#include <Core/Config/ConfigFile.h>

std::unique_ptr<Config::Settings> getSettings(const std::string& filename) {
	auto settings = std::make_unique<Config::Settings>();
	settings->registerSettings(Config::SettingsMap{{"database", ""}});

	Config::ConfigFile(filename, settings.get()).read();

	return settings;
}

