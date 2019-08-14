#ifndef __DONE_ACTION_TEST
#define __DONE_ACTION_TEST

#include <string>

#include "Core/DateTime/Timestamp.h"

#include "HT/Actions/IAction.h"
#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class DoneAction : public IAction
{
public:
	DoneAction();
	void setDaoFactory(Dao::DaoFactory* daoFactory);
	void execute(const Cli::Parameters& parameters);

private:
	void validateParameters(const Cli::Parameters& parameters) const;
	Dt::Timestamp getDate(const Cli::Parameters& parserResult) const;

private:
	std::shared_ptr<Dao::IHabitDao> habitDao;
	std::shared_ptr<Dao::IHabitDefinitionDao> definitionDao;
};

} // namespace Actions

#endif // __DONE_ACTION_TEST
