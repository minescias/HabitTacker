#ifndef __BASE_COMMAND_H
#define __BASE_COMMAND_H

#include "HtCli/Actions/ICommand.h"

namespace CLI
{
class App;
} // namespace CLI

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
