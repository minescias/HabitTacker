#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <string>

class Settings
{
public:
	Settings();

	std::string getDatabaseName() const;
	void setDatabaseName(const std::string& databaseName);

private:
	std::string databaseName;
};


#endif // __SETTINGS_H
