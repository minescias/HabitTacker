#ifndef __DEFAULT_ACTION_H
#define __DEFAULT_ACTION_H

#include <map>

#include <Core/DateTime/Timestamp.h>

#include "HT/Actions/BaseAction.h"
#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class DefaultAction : public BaseAction
{
	enum class CompletionType
	{
		None,
		Yes,
		No
	};

	using CompletionTable = std::map<int, std::vector<CompletionType>>;

public:
	DefaultAction();

protected:
	void initValidator() final;
	void doExecute(const Cli::Parameters &parameters) final;

private:
	void printHeader(Dt::Timestamp date) const;
	std::string getWeekDaysHeaderEndingWithDate(Dt::Timestamp date) const;
	std::string getCompletionString(int habitId);
	void fillCompletionTable(Dt::Timestamp date);

	void prepareCompletionTable(Dt::Timestamp date,
		const Entity::HabitDefinitions& definitions);

private:
	int daysToPrint;
	std::shared_ptr<Dao::IHabitDao> habitDao;
	std::shared_ptr<Dao::IHabitDefinitionDao> definitionDao;
	CompletionTable completionTable;
};

}

#endif // __DEFAULT_ACTION_H
