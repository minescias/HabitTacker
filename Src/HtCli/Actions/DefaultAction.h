#ifndef __DEFAULT_ACTION_H
#define __DEFAULT_ACTION_H

#include <map>

#include "Core/Cli/Table.h"

#include "Core/DateTime/Date.h"
#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"
#include "HtCli/Actions/BaseCommand.h"

namespace Commands
{
class ShowCommand : public BaseCommand
{
public:
	ShowCommand();
	void execute() final;
	void setCliParameters(CLI::App* app) final;

protected:
	// void initValidator() final;

private:
	void addWeekdayColumns(Dt::Date date);
	void initWeekdayValues(Entity::HabitDefinitionEntity& definition, Dt::Date date);
	void fillWeekdayValues(Entity::HabitDefinitionEntity& definition, Dt::Date date);

private:
	std::string dateStr;
	Dt::Date date;
	int daysToPrint;
	std::shared_ptr<Dao::IHabitDao> habitDao;
	std::shared_ptr<Dao::IHabitDefinitionDao> definitionDao;

	Cli::Table table;
};

} // namespace Commands

#endif // __DEFAULT_ACTION_H
