#ifndef __ACTION_H
#define __ACTION_H

#include "HT/Cli/ParserResult.h"
#include "HT/Dao/DaoFactory.h"

namespace Actions
{

class IAction
{
public:
	virtual void setDaoFactory(Dao::DaoFactory* daoFactory) = 0;

	// temporary a non pure virtual to be able to implement it one class
	virtual void execute(const Cli::ParserResult& parserResult){};

	virtual ~IAction(){}
};

} // namespace Actions

#endif
