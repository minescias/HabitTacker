#ifndef __INIT_ACTION
#define __INIT_ACTION

#include <string>

#include "Core/Cli/Parameters.h"
#include "Core/Cli/Validator.h"

namespace Actions
{
class InitAction
{
public:
	InitAction();
	void execute(const Cli::Parameters& parameters);

private:
	void initValidator();
	void createDatabaseFile() const;
	void createConfigFile(bool globallyAccesible) const;

private:
	std::string dbFilename;
	std::string configFileName;
	Cli::Validator validator;
};

} // namespace Actions

#endif
