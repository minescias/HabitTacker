#ifndef __DONE_ACTION_TEST
#define __DONE_ACTION_TEST

#include <string>

#include "HT/Dao/IHabitDao.h"

namespace Actions
{

class DoneAction
{
public:
	DoneAction(Dao::IHabitDao* habitDao);
	void execute(const std::string& habitId);

private:
	Dao::IHabitDao* habitDao;
};

} // namespace Actions

#endif // __DONE_ACTION_TEST