#ifndef __EDIT_ACTION_H
#define __EDIT_ACTION_H

#include <string>

#include "HtCli/Commands/BaseCommand.h"

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
};

} // namespace Actions

#endif // __EDIT_ACTION_H
