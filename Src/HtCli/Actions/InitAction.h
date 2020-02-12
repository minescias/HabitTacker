#ifndef __INIT_ACTION
#define __INIT_ACTION

#include <string>

#include "Core/Cli/Parameters.h"
#include "Core/Cli/Validator.h"

namespace CLI
{
struct App;
} // namespace CLI

namespace Actions
{
class InitAction
{
public:
	InitAction();
	void execute();
	void addCliOptions(CLI::App* app);

private:
	void createDatabaseFile() const;
	void createConfigFile() const;

private:
	bool global;
	std::string dbFilename;
	std::string configFileName;
};

} // namespace Actions

#endif
