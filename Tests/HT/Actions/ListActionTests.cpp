#include <gmock/gmock.h>

#include "HT/Actions/ListAction.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/Tools/RegisterAndGetDaoMock.h"

namespace Tests
{

using namespace testing;

class ListActionTest : public testing::Test
{
public:
	ListActionTest()
	{
		daoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
			&factory, "habitDefinition");

		listAction.setDaoFactory(&factory);
	}

	Entity::HabitDefinitionEntityPtr getHabit(int id, const std::string& name)
	{
		auto entity = std::make_unique<Entity::HabitDefinitionEntity>();

		entity->setId(id);
		entity->setName(name);

		return entity;
	}

	std::vector<Entity::HabitDefinitionEntityPtr> getHabits()
	{
		std::vector<Entity::HabitDefinitionEntityPtr> habits;
		habits.emplace_back(getHabit(1, "Pierwszy"));
		habits.emplace_back(getHabit(2, "Drugi"));

		return habits;
	}

	void testForOutput(const std::string& expectedOutput)
	{
		internal::CaptureStdout();
		listAction.execute(Cli::ParserResult());

		auto output = testing::internal::GetCapturedStdout();
		ASSERT_STREQ(output.c_str(), expectedOutput.c_str());
	}

	std::shared_ptr<Mocks::HabitDefinitionDaoMock> daoMock;
	Actions::ListAction listAction;
	Dao::DaoFactory factory;
};

TEST_F(ListActionTest, getsDefinitionsFromDao)
{
	EXPECT_CALL(*daoMock, getDefinitions()).Times(1);
	listAction.execute(Cli::ParserResult());
}

TEST_F(ListActionTest, printsMessageWhenNoHabitsFound)
{
	EXPECT_CALL(*daoMock, getDefinitions()).WillOnce(
		Return(ByMove(std::vector<Entity::HabitDefinitionEntityPtr>())));

	auto expectedOutput = "No habits found, try to add some using 'htr add'\n";

	testForOutput(expectedOutput);
}

TEST_F(ListActionTest, printsAllDefinitionsTest)
{
	EXPECT_CALL(*daoMock, getDefinitions()).WillOnce(
		Return(ByMove(getHabits())));

	auto expectedOutput =
		"\nid   name"
		"\n---- ----------------------------------------"
		"\n   1 Pierwszy"
		"\n   2 Drugi"
		"\n"
	;

	testForOutput(expectedOutput);
}

} // namespace Tests
