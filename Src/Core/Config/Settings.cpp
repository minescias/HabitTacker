#include "Core/Config/Settings.h"

#include "Core/Utils/Exceptions/RuntimeError.h"

Settings::Settings()
{
	setDefaultValues();
}

void Settings::setDefaultValues()
{
	settingsMap["database"] = "";
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
