#ifndef __ADD_ACTION_H
#define __ADD_ACTION_H

#include <string>

#include "HtCli/Commands/BaseCommand.h"

namespace Commands
{
class AddCommand : public BaseCommand
{
public:
	AddCommand() = default;

	void setCliParameters(CLI::App* app) final;
	void execute() final;

private:
	unsigned int target;
	std::string name;
};

} // namespace Commands

#endif
