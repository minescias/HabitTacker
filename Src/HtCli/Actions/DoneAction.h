#ifndef __DONE_ACTION_TEST
#define __DONE_ACTION_TEST

#include <string>

#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"
#include "HT/Dao/IRequirementDao.h"
#include "HtCli/Actions/BaseAction.h"

namespace Actions
{
class DoneAction : public BaseAction
{
public:
	DoneAction() = default;

protected:
	void initValidator() final;
	void doExecute(const Cli::Parameters& parameters) final;

private:
	void validateParameters(const Cli::Parameters& parameters) const;
	Dt::Date getDate(const Cli::Parameters& parameters) const;
	int getResult(const Cli::Parameters& parameters, int definitionId) const;

private:
	std::shared_ptr<Dao::IHabitDao> habitDao;
	std::shared_ptr<Dao::IHabitDefinitionDao> definitionDao;
	std::shared_ptr<Dao::IRequirementDao> requirementDao;
};

} // namespace Actions

#endif // __DONE_ACTION_TEST
