#include "HT/AppInit/Settings.h"

Settings::Settings()
{
}

std::string Settings::getDatabaseName() const
{
	return databaseName;
}

void Settings::setDatabaseName(const std::string& databaseName)
{
	this->databaseName = databaseName;
}

