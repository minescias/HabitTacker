#ifndef __DONE_ACTION_TEST
#define __DONE_ACTION_TEST

#include <string>

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
	void execute(const Cli::ParserResult& parserResult);

private:
	std::unique_ptr<Dao::IHabitDao> habitDao;
	std::unique_ptr<Dao::IHabitDefinitionDao> definitionDao;
};

} // namespace Actions

#endif // __DONE_ACTION_TEST
