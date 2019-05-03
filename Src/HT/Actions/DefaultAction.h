#ifndef __DEFAULT_ACTION_H
#define __DEFAULT_ACTION_H

#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class DefaultAction
{
public:
	DefaultAction(Dao::IHabitDao* habitDao, Dao::IHabitDefinitionDao* definitionDao);
	void execute(time_t date);

private:
	void printHeader(time_t date) const;
	std::string getWeekDaysHeaderEndingWithDate(time_t date) const;

private:
	Dao::IHabitDao* habitDao;
	Dao::IHabitDefinitionDao* definitionDao;
};

};

#endif // __DEFAULT_ACTION_H