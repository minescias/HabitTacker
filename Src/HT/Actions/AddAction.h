#ifndef __ADD_ACTION_H
#define __ADD_ACTION_H

#include <string>

#include "HT/Actions/IAction.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class AddAction : public IAction
{
public:
	AddAction();
	virtual void setDaoFactory(Dao::DaoFactory* daoFactory);
	virtual void execute(const Cli::ParserResult& parserResult);

private:
	std::shared_ptr<Dao::IHabitDefinitionDao> dao;
};

} // namespace Actions

#endif
