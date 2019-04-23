#include <gmock/gmock.h>

#include "HT/Actions/AddAction.h"

using namespace testing;

class HabitDefinitionDaoMock : public Dao::IHabitDefinitionDao
{
public:
	MOCK_METHOD1(saveDefinition, void(const Entity::HabitDefinitionEntity& entity));
	MOCK_METHOD1(getDefinition, Entity::HabitDefinitionEntityPtr (int definitionId));
};

class AddActionTest : public testing::Test
{
public:
	AddActionTest()
		: daoMock(std::make_unique<HabitDefinitionDaoMock>())
		, addAction(daoMock.get())
	{
	}

	std::unique_ptr<HabitDefinitionDaoMock> daoMock;
	Actions::AddAction addAction;
};

TEST_F(AddActionTest, savesHabitToDatabase)
{
	Entity::HabitDefinitionEntity entity;
	entity.setName("new habit name");

	EXPECT_CALL(*daoMock, saveDefinition(entity));

	addAction.execute("new habit name");
}
