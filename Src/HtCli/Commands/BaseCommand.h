#ifndef __BASE_COMMAND_H
#define __BASE_COMMAND_H

#include "HtCli/Commands/ICommand.h"

namespace Commands
{
class BaseCommand : public ICommand
{
public:
	BaseCommand() = default;
	virtual ~BaseCommand() = default;

	void setDaoFactory(Dao::DaoFactory* daoFactory) final;

protected:
	Dao::DaoFactory* daoFactory;
};

} // namespace Commands

#endif // __BASE_COMMAND_H
