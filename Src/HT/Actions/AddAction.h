#ifndef __ADD_ACTION_H
#define __ADD_ACTION_H

#include <string>

#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class AddAction
{
public:
	AddAction(Dao::IHabitDefinitionDao* dao);
	void execute(const std::string& habitName);

private:
	Dao::IHabitDefinitionDao* dao;
};

} // namespace Actions

#endif
