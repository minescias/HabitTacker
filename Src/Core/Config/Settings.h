#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <map>
#include <string>

namespace Config
{

using SettingsMap = std::map<std::string, std::string>;

class Settings
{
public:
	Settings();

	void registerSettings(const SettingsMap& settings);

	std::string get(const std::string& name) const;
	void set(const std::string& name, const std::string& value);

private:
	void setDefaultValues();

private:
	SettingsMap settingsMap;
};

} // namespace Config

#endif // __SETTINGS_H
