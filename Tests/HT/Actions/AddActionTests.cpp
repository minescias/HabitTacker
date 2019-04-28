#include <gmock/gmock.h>

#include "HT/Actions/AddAction.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"

using namespace testing;

class AddActionTest : public testing::Test
{
public:
	AddActionTest()
		: daoMock(std::make_unique<Mocks::HabitDefinitionDaoMock>())
		, addAction(daoMock.get())
	{
	}

	std::unique_ptr<Mocks::HabitDefinitionDaoMock> daoMock;
	Actions::AddAction addAction;
};

TEST_F(AddActionTest, savesHabitToDatabase)
{
	Entity::HabitDefinitionEntity entity;
	entity.setName("new habit name");

	EXPECT_CALL(*daoMock, saveDefinition(entity));

	addAction.execute("new habit name");
}
