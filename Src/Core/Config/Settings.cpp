#include "Core/Config/Settings.h"

#include "Core/Exceptions/RuntimeError.h"

namespace Config
{
Settings::Settings()
{
}

void Settings::registerSettings(const SettingsMap& settings)
{
	settingsMap = settings;
}

std::string Settings::get(const std::string& name) const
{
	if (settingsMap.find(name) == settingsMap.end())
		throw RuntimeError("Trying to get unknown setting " + name);

	return settingsMap.at(name);
}

void Settings::set(const std::string& name, const std::string& value)
{
	if (settingsMap.find(name) == settingsMap.end())
		throw RuntimeError("Trying to set unknown setting " + name);

	settingsMap.at(name) = value;
}

SettingsMap Settings::getAllSettings() const
{
	return settingsMap;
}

} // namespace Config
