#ifndef __DONE_ACTION_TEST
#define __DONE_ACTION_TEST

#include <string>

#include "HT/Dao/IHabitDao.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class DoneAction
{
public:
	DoneAction(Dao::IHabitDao* habitDao, Dao::IHabitDefinitionDao* definitionDao);
	void execute(const std::string& habitId);

private:
	Dao::IHabitDao* habitDao;
	Dao::IHabitDefinitionDao* definitionDao;
};

} // namespace Actions

#endif // __DONE_ACTION_TEST