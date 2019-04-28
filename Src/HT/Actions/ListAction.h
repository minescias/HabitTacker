#ifndef __LIST_ACTION_H
#define __LIST_ACTION_H

#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class ListAction
{
public:
	ListAction(Dao::IHabitDefinitionDao* dao);

	void execute();

private:
	void printHeader() const;

private:
	Dao::IHabitDefinitionDao* dao;
};

} // namespace Actions

#endif
