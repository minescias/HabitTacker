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

	void execute(const std::string& habitName);

private:
	std::unique_ptr<Dao::IHabitDefinitionDao> dao;
};

} // namespace Actions

#endif
