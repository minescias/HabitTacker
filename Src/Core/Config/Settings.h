#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <map>
#include <string>

class Settings
{
	using SettingsMap = std::map<std::string, std::string>;

public:
	Settings();

	std::string get(const std::string& name) const;
	void set(const std::string& name, const std::string& value);

private:
	void setDefaultValues();

private:
	SettingsMap settingsMap;
};
#endif // __SETTINGS_H
