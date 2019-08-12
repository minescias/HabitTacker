#ifndef __ACTION_H
#define __ACTION_H

#include "Core/Cli/ParserResult.h"
#include "Core/Dao/DaoFactory.h"

namespace Actions
{

class IAction
{
public:
	virtual void setDaoFactory(Dao::DaoFactory* daoFactory) = 0;
	virtual void execute(const Cli::ParserResult& parserResult) = 0;

	virtual ~IAction(){}
};

} // namespace Actions

#endif
