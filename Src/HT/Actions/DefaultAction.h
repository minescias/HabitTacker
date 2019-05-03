#ifndef __DEFAULT_ACTION_H
#define __DEFAULT_ACTION_H

#include <map>

#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class DefaultAction
{
	using CompletionTable = std::map<int, std::vector<bool>>;

public:
	DefaultAction(Dao::IHabitDao* habitDao, Dao::IHabitDefinitionDao* definitionDao);
	void execute(time_t date);

private:
	void printHeader(time_t date) const;
	std::string getWeekDaysHeaderEndingWithDate(time_t date) const;
	std::string getCompletionString(int habitId);

	void prepareCompletionTable(
		const std::vector<Entity::HabitDefinitionEntityPtr>& definitions);

	void fillCompletionTable(
		const std::vector<Entity::HabitEntityPtr>& habits, time_t date);

private:
	Dao::IHabitDao* habitDao;
	Dao::IHabitDefinitionDao* definitionDao;
	CompletionTable completionTable;
};

};

#endif // __DEFAULT_ACTION_H
