#ifndef __INIT_ACTION
#define __INIT_ACTION

#include <string>

namespace Actions
{

class InitAction
{
public:
	InitAction();
	void execute(const std::string& dbFilePath, const std::string& configFilePath);

private:
	void createDatabaseFile() const;
	void createConfigFile() const;

private:
	std::string dbFilename;
	std::string configFilename;
};

} // namespace Actions

#endif
