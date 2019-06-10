#include <gmock/gmock.h>

#include "HT/Actions/ActionError.h"
#include "HT/Actions/AddAction.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/Tools/DaoMockCreator.h"

namespace Tests
{

using namespace testing;

class AddActionTests : public testing::Test
{
public:
	AddActionTests()
	{
		daoMock = new Mocks::HabitDefinitionDaoMock();
		factory.registerDao("habitDefinition", createDaoMock(daoMock));
		addAction.setDaoFactory(&factory);

		pr = Cli::ParserResult("add", "", Cli::Arguments{{"", ""}});
	}

	Mocks::HabitDefinitionDaoMock* daoMock;
	Dao::DaoFactory factory;
	Actions::AddAction addAction;
	Cli::ParserResult pr;
};

TEST_F(AddActionTests, savesHabitToDatabase)
{
	Entity::HabitDefinitionEntity entity;
	entity.setName("new habit name");
	EXPECT_CALL(*daoMock, saveDefinition(entity));

	pr.arguments = Cli::Arguments{{"", "new habit name"}};
	addAction.execute(pr);
}

TEST_F(AddActionTests, ensures_that_name_is_not_empty)
{
	try
	{
		addAction.execute(pr);
		FAIL() << "Action error expected";
	}
	catch(Actions::ActionError& err)
	{
		auto expected{"No habit name specified"};
		ASSERT_STREQ(err.what(), expected);
	}

}

} // namespace Tests
