#ifndef __ACTION_H
#define __ACTION_H

#include "CLI/App.hpp"

#include "Core/Cli/Parameters.h"
#include "Core/Dao/DaoFactory.h"

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

} // namespace Actions

#endif
