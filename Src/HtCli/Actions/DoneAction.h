#ifndef __DONE_ACTION_TEST
#define __DONE_ACTION_TEST

#include <optional>
#include <string>
#include <vector>

#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"
#include "HT/Dao/IRequirementDao.h"
#include "HtCli/Actions/BaseCommand.h"

namespace Commands
{
class DoneCommand : public Commands::BaseCommand
{
public:
	DoneCommand() = default;

	void execute() final;
	void setCliParameters(CLI::App* app) final;

private:
	void validateParameters() const;
	Dt::Date getDate() const;
	int getResult() const;

private:
	int habitId;
	bool reset;
	std::string dateStr;
	std::optional<int> result;
	std::shared_ptr<Dao::IHabitDao> habitDao;
	std::shared_ptr<Dao::IHabitDefinitionDao> definitionDao;
	std::shared_ptr<Dao::IRequirementDao> requirementDao;
};

} // namespace Commands

#endif // __DONE_ACTION_TEST
