#include <gmock/gmock.h>

#include "HT/Actions/AddAction.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/Tools/DaoMockCreator.h"

using namespace testing;

namespace Tests
{

TEST(AddActionTest, savesHabitToDatabase)
{
	auto daoMock = new Mocks::HabitDefinitionDaoMock();

	Entity::HabitDefinitionEntity entity;
	entity.setName("new habit name");
	EXPECT_CALL(*daoMock, saveDefinition(entity));

	Dao::DaoFactory factory;
	factory.registerDao("habitDefinition", createDaoMock(daoMock));

	auto pr = Cli::ParserResult("add", "",
		Cli::Arguments{{"", "new habit name"}});

	auto addAction = Actions::AddAction();
	addAction.setDaoFactory(&factory);
	addAction.execute(pr);
}

} // namespace Tests
