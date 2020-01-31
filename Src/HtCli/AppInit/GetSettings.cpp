#include "HtCli/AppInit/GetSettings.h"
#include "fmt/posix.h"

#include <filesystem>
#include <pwd.h>
#include <string>
#include <unistd.h>

#include <Core/Config/ConfigFile.h>

namespace
{
namespace fs = std::filesystem;

std::string getConfigFilePath()
{
	auto filename = "htr_settings.json";
	if (fs::exists(filename))
		return filename;

	auto homeDir = getenv("HOME");
	if (!homeDir)
		homeDir = getpwuid(getuid())->pw_dir;

	return fs::path(homeDir).append(".config/htr").append(filename).c_str();
}

} // namespace

std::unique_ptr<Config::Settings> getSettings()
{
	auto settings = std::make_unique<Config::Settings>();
	settings->registerSettings(Config::SettingsMap{{"database", ""}});

	Config::ConfigFile(getConfigFilePath(), settings.get()).read();

	return settings;
}
