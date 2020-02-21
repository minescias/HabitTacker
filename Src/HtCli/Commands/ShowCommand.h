#ifndef __DEFAULT_ACTION_H
#define __DEFAULT_ACTION_H

#include <map>

#include "Core/Cli/Table.h"
#include "Core/DateTime/Date.h"

#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"
#include "HtCli/Commands/BaseCommand.h"

namespace Commands
{
class ShowCommand : public BaseCommand
{
public:
	ShowCommand();
	void execute() final;
	void setCliParameters(CLI::App* app) final;

private:
	void addWeekdayColumns(Dt::Date date);
	void initWeekdayValues(Entity::HabitDefinitionEntity& definition, Dt::Date date);
	void fillWeekdayValues(Entity::HabitDefinitionEntity& definition, Dt::Date date);

private:
	int daysToPrint;
	Dt::Date date;
	Cli::Table table;
	std::string dateStr;
	std::shared_ptr<Dao::IHabitDao> habitDao;
	std::shared_ptr<Dao::IHabitDefinitionDao> definitionDao;
};

} // namespace Commands

#endif // __DEFAULT_ACTION_H
