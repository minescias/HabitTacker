#include "HT/Actions/DoneAction.h"

namespace Actions
{

DoneAction::DoneAction(Dao::IHabitDao* habitDao)
	:habitDao(habitDao)
{

}

void DoneAction::execute(const std::string& habitId)
{
	auto today = time(nullptr);
	today -= (today % 86400); // 86400 = 24 * 60 * 60

	auto habit = Entity::HabitEntity();
	habit.setHabitId(stoi(habitId));
	habit.setDate(today);

	habitDao->saveHabit(habit);
}

} // namespace Actions
