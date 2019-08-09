#include <gmock/gmock.h>

#include "Core/Exceptions/LogicError.h"

#include "HT/Dao/DaoFactory.h"
#include "HT/Dao/UnknownDao.h"

namespace
{

using namespace testing;

class IDummyDao : public Dao::UnknownDao
{
public:
	virtual int foo() = 0;
	virtual Db::Database* getDatabasePointer() = 0;

	virtual ~IDummyDao(){};
};

class SomeDummyDao : public IDummyDao
{
public:
	SomeDummyDao(Db::Database* db) :db(db) {}
	virtual int foo(){return 2342;}
	virtual Db::Database* getDatabasePointer() {return db;}

private:
	Db::Database* db;
};

class DummmyDaoMock : public IDummyDao
{
public:
	MOCK_METHOD0(foo, int());
	MOCK_METHOD0(getDatabasePointer, Db::Database*());
};

class IOtherDummyDao : public Dao::UnknownDao
{
public:
	virtual int bar(){return 0;};

	virtual ~IOtherDummyDao(){};
};

} // namespace

namespace Tests
{

class DaoFactoryTests : public testing::Test
{
public:
	DaoFactoryTests()
	{
	}

	Dao::DaoFactory daoFactory;
};

TEST_F(DaoFactoryTests, allows_to_register_and_get_dao)
{
	daoFactory.registerDao("someDao", [](Db::Database* db) -> Dao::UnknownDaoPtr
		{ return std::make_shared<SomeDummyDao>(db); });

	auto someDao = daoFactory.createDao<IDummyDao>("someDao");
	ASSERT_EQ(someDao->foo(), 2342);
}

TEST_F(DaoFactoryTests, returns_the_dame_dao_when_created_more_than_once)
{
	daoFactory.registerDao("someDao", [](Db::Database* db) -> Dao::UnknownDaoPtr
		{ return std::make_shared<SomeDummyDao>(db); });

	auto someDao = daoFactory.createDao<IDummyDao>("someDao");
	auto someDao2 = daoFactory.createDao<IDummyDao>("someDao");

	ASSERT_TRUE(someDao.get() == someDao2.get());
}

TEST_F(DaoFactoryTests, destroys_dao_when_no_one_is_using_it)
{
	daoFactory.registerDao("someDao", [](Db::Database* db) -> Dao::UnknownDaoPtr
		{ return std::make_shared<SomeDummyDao>(db); });

	Dao::UnknownDao* firstDaoPtr;

	{
		auto firstDao = daoFactory.createDao<IDummyDao>("someDao");
		EXPECT_THAT(firstDao.use_count(), Eq(1)); //ensure that dao was created
		firstDaoPtr = firstDao.get(); //saving the first dao address
	}	// first dao get destroyed here

	auto secondDao = daoFactory.createDao<IDummyDao>("someDao");
	ASSERT_FALSE(firstDaoPtr == secondDao.get());
}

TEST_F(DaoFactoryTests, allowsToRegisterAndGetDaoMock)
{
	daoFactory.registerDao("someDao", [](Db::Database* db) -> Dao::UnknownDaoPtr
		{ return std::make_shared<DummmyDaoMock>(); });

	auto daoMock = daoFactory.createDao<DummmyDaoMock>("someDao");
	EXPECT_CALL(*daoMock, foo()).WillOnce(Return(9786));

	auto someDao = daoFactory.createDao<IDummyDao>("someDao");
	ASSERT_EQ(someDao->foo(), 9786);
}

TEST_F(DaoFactoryTests, passesDatabaseToNewlyCreatedDao)
{
	// I dont want to create full Db::Database object here. Instad I'm creating
	// an int and setting its addres to the pointer of Db::Database :)
	auto i{3};
	Db::Database* db = reinterpret_cast<Db::Database*>(i);

	daoFactory.setDatabase(db);

	daoFactory.registerDao("someDao", [](Db::Database* db) -> Dao::UnknownDaoPtr
		{ return std::make_unique<SomeDummyDao>(db); });

	auto someDao = daoFactory.createDao<IDummyDao>("someDao");

	ASSERT_EQ(db, someDao->getDatabasePointer());
}

TEST_F(DaoFactoryTests, throwsLogicErrorWhenDaoIsRegisteredTwice)
{
	daoFactory.registerDao("someDao", [](Db::Database* db) -> Dao::UnknownDaoPtr
		{ return std::make_unique<SomeDummyDao>(db); });

	try
	{
		daoFactory.registerDao("someDao", [](Db::Database* db) -> Dao::UnknownDaoPtr
			{ return std::make_unique<SomeDummyDao>(db); });

		FAIL() << "Expected logic error";
	}
	catch(LogicError& err)
	{
		auto expected = "DaoFactory: someDao was already registered";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(DaoFactoryTests, throwsLogicErrorAccessingUnregisteredDao)
{
	try
	{
		daoFactory.createDao<IDummyDao>("unregisteredDao");

		FAIL() << "Expected logic error";
	}
	catch(LogicError& err)
	{
		auto expected = "DaoFactory: unregisteredDao is not registered";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(DaoFactoryTests, throwsLogicErrorWhenTryingToCastDaoToWrongType)
{
	daoFactory.registerDao("someDao", [](Db::Database* db) -> Dao::UnknownDaoPtr
		{ return std::make_unique<SomeDummyDao>(db); });

	try
	{
		auto someDao = daoFactory.createDao<IOtherDummyDao>("someDao");
		FAIL() << "Expected logic error";
	}
	catch(LogicError& err)
	{
		auto expected = "DaoFactory: trying to cast someDao to wrong type";
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
