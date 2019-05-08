#ifndef __DEFAULT_ACTION_H
#define __DEFAULT_ACTION_H

#include <map>

#include "HT/Actions/IAction.h"
#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class DefaultAction : public IAction
{
	using CompletionTable = std::map<int, std::vector<bool>>;

public:
	DefaultAction();
	void setDaoFactory(Dao::DaoFactory* daoFactory);
	void execute(time_t date);

private:
	void printHeader(time_t date) const;
	std::string getWeekDaysHeaderEndingWithDate(time_t date) const;
	std::string getCompletionString(int habitId);
	void fillCompletionTable(time_t date);

	void prepareCompletionTable(
		const std::vector<Entity::HabitDefinitionEntityPtr>& definitions);

private:
	std::unique_ptr<Dao::IHabitDao> habitDao;
	std::unique_ptr<Dao::IHabitDefinitionDao> definitionDao;
	CompletionTable completionTable;
};

};

#endif // __DEFAULT_ACTION_H
