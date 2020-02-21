#ifndef __COMMAND_H
#define __COMMAND_H

#include "Core/Dao/DaoFactory.h"
#include "Core/Fwd/CLI_fwd.h"

namespace Commands
{
class ICommand
{
public:
	virtual void setDaoFactory(Dao::DaoFactory* daoFactory) = 0;
	virtual void setCliParameters(CLI::App* app) = 0;
	virtual void execute() = 0;

	virtual ~ICommand() = default;
};

} // namespace Commands

#endif
