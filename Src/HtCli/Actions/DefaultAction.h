#ifndef __DEFAULT_ACTION_H
#define __DEFAULT_ACTION_H

#include <map>

#include "Core/Cli/Table.h"

#include "HtCli/Actions/BaseAction.h"
#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{
class DefaultAction : public BaseAction
{
public:
	DefaultAction();

protected:
	void initValidator() final;
	void doExecute(const Cli::Parameters& parameters) final;

private:
	void addWeekdayColumns(Dt::Date date);
	void initWeekdayValues(Entity::HabitDefinitionEntity& definition, Dt::Date date);
	void fillWeekdayValues(Entity::HabitDefinitionEntity& definition, Dt::Date date);

private:
	int daysToPrint;
	std::shared_ptr<Dao::IHabitDao> habitDao;
	std::shared_ptr<Dao::IHabitDefinitionDao> definitionDao;

	Cli::Table table;
};

} // namespace Actions

#endif // __DEFAULT_ACTION_H
