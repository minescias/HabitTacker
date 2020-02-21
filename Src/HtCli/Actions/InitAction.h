#ifndef __INIT_ACTION
#define __INIT_ACTION

#include <string>

#include "Core/Cli/Parameters.h"
#include "Core/Cli/Validator.h"
#include "HtCli/Actions/ICommand.h"

namespace Commands
{
class InitCommand : public ICommand
{
public:
	InitCommand();
	void execute();
	void setCliParameters(CLI::App* app) final;
	void setDaoFactory(Dao::DaoFactory* daoFactory) final;

private:
	void createDatabaseFile() const;
	void createConfigFile() const;

private:
	bool global;
	std::string dbFilename;
	std::string configFileName;
};

} // namespace Commands

#endif
