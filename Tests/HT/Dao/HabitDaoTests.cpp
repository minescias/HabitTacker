#include <gmock/gmock.h>

#include <filesystem>
#include <iomanip>
#include <memory>

#include <Core/DateTime/DateTimeGetter.h>
#include <Core/DateTime/Operators.h>

#include "HT/Dao/DatabaseCreator.h"
#include "HT/Dao/HabitDao.h"
#include "HT/Dao/HabitDefinitionDao.h"

namespace Tests
{
using date::days;
using namespace testing;
namespace fs = std::filesystem;

MATCHER_P(HabitEq, expected, "Compared two habits")
{
	EXPECT_THAT(arg.getHabitId(), Eq(expected.getHabitId()));
	EXPECT_THAT(arg.getDate(), Eq(expected.getDate()));
	EXPECT_THAT(arg.getResult(), Eq(expected.getResult()));
	return true;
}

class HabitDaoTests : public testing::Test
{
public:
	HabitDaoTests() : filename("test_files/Ht_HabitDao.db")
	{
		fs::remove(filename);
		db = Dao::DatabaseCreator{filename}.createEmptyDatabase();
		definitionDao = std::make_unique<Dao::HabitDefinitionDao>(db.get());
		habitDao = std::make_unique<Dao::HabitDao>(db.get());
	}

	void addDefinition(const std::string& name)
	{
		Entity::HabitDefinitionEntity definition;
		definition.setName(name);

		definitionDao->saveDefinition(definition);
	}

	auto addHabit(int habitId, Dt::Date date)
	{
		auto habit = Entity::HabitEntity();
		habit.setHabitId(habitId);
		habit.setDate(date);
		habit.setResult(1);

		habitDao->saveHabit(habit);
		return habit;
	}

	std::string filename;
	std::unique_ptr<Db::Database> db;
	std::unique_ptr<Dao::IHabitDefinitionDao> definitionDao;
	std::unique_ptr<Dao::IHabitDao> habitDao;
};

TEST_F(HabitDaoTests, save_and_read_test)
{
	addDefinition("Some definition");

	auto writtenHabit = Entity::HabitEntity();
	writtenHabit.setHabitId(1);
	writtenHabit.setDate(Dt::getCurrentDate());
	writtenHabit.setResult(12);

	habitDao->saveHabit(writtenHabit);
	auto readHabits = habitDao->getHabitsById(1);

	ASSERT_THAT(readHabits.size(), Eq(1));
	EXPECT_THAT(*readHabits[0], HabitEq(writtenHabit));
}

TEST_F(HabitDaoTests, checksIfHabitIsSetForDay)
{
	addDefinition("Some definition");

	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());

	ASSERT_FALSE(habitDao->checkIfHabitIsSetForDay(habit));
	habitDao->saveHabit(habit);
	ASSERT_TRUE(habitDao->checkIfHabitIsSetForDay(habit));
}

TEST_F(HabitDaoTests, gets_habits_from_given_period)
{
	auto today = Dt::getCurrentDate();

	addDefinition("Some definition");
	addDefinition("Excluded definition");

	// included data
	auto expected =
		std::vector<Entity::HabitEntity>{{addHabit(1, today - days{13})},
										 {addHabit(1, today - days{10})},
										 {addHabit(1, today - days{2})},
										 {addHabit(1, today - days{1})},
										 {addHabit(1, today)}};

	// excluded data: over 14 days and other habit
	addHabit(1, today - days{14});
	addHabit(1, today - days{15});
	addHabit(2, today - days{2});

	auto habits = habitDao->getHabits(1, today - days{13}, today);

	ASSERT_THAT(habits.size(), Eq(5));
	for (unsigned i = 0; i < habits.size(); i++)
		EXPECT_THAT(*habits[i], HabitEq(expected[i]));
}

TEST_F(HabitDaoTests, deleteHabitTests)
{
	addDefinition("Some definition");

	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());

	habitDao->saveHabit(habit);
	ASSERT_TRUE(habitDao->checkIfHabitIsSetForDay(habit));
	habitDao->deleteHabit(habit);
	ASSERT_FALSE(habitDao->checkIfHabitIsSetForDay(habit));
}

} // namespace Tests
