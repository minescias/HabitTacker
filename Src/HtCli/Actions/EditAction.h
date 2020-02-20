#ifndef __EDIT_ACTION_H
#define __EDIT_ACTION_H

#include "HtCli/Actions/BaseCommand.h"
#include <string>

namespace Commands
{

class EditCommand : public BaseCommand
{
public:
	EditCommand() = default;
	
	void execute() final;
	void setCliParameters(CLI::App* app) final;
private:
	int habitId;
	std::string name;
// protected:
// 	void initValidator() final;
// 	void doExecute(const Cli::Parameters& parameters);
};

} // namespace Actions

#endif // __EDIT_ACTION_H
