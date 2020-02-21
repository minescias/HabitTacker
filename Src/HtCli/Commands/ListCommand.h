#ifndef __LIST_ACTION_H
#define __LIST_ACTION_H

#include "HT/Dao/IHabitDefinitionDao.h"
#include "HtCli/Commands/BaseCommand.h"

namespace Commands
{
class ListCommand : public BaseCommand
{
public:
	ListCommand() = default;

	void execute() final;
	void setCliParameters(CLI::App* app) final;

private:
	void printHeader() const;
};

} // namespace Commands

#endif
