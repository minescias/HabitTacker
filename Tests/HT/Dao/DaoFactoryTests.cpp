#include <gmock/gmock.h>

#include "Core/Utils/Exceptions/LogicError.h"

#include "HT/Dao/DaoFactory.h"
#include "HT/Dao/UnknownDao.h"

#include "Tests/Tools/DaoMockCreator.h"

using namespace testing;

namespace
{

class IDummyDao : public Dao::UnknownDao
{
public:
	virtual int foo() = 0;

	virtual ~IDummyDao(){};
};

class SomeDummyDao : public IDummyDao
{
public:
	SomeDummyDao(){}
	virtual int foo(){return 2342;}
};

class DummmyDaoMock : public IDummyDao
{
public:
	MOCK_METHOD0(foo, int());
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

TEST_F(DaoFactoryTests, allowsToRegisterAndGetDao)
{
	daoFactory.registerDao("someDao", []() -> Dao::UnknownDaoPtr
		{ return std::make_unique<SomeDummyDao>(); });

	auto someDao = daoFactory.createDao<IDummyDao>("someDao");
	ASSERT_EQ(someDao->foo(), 2342);
}

TEST_F(DaoFactoryTests, allowsToRegisterAndGetDaoMock)
{
	auto daoMock = new DummmyDaoMock(); //grrr...
	EXPECT_CALL(*daoMock, foo()).WillOnce(Return(9786));

	daoFactory.registerDao("someDao", createDaoMock(daoMock));

	auto someDao = daoFactory.createDao<IDummyDao>("someDao");
	ASSERT_EQ(someDao->foo(), 9786);

	// jeśli dao nigdy nie zostanie utworzone to nie będzie uniqie_ptr, który
	// usunąłby później to co jest pod wskaźnikiem - wyciek pamięci, dlatego
	// muszę robić to ręcznie tutaj

	// żeby było jeszcze śmieszniej akurat w tym przypadku nie mogę usuwać 
	// wskaźnika ręcznie bo unique_ptr spróbuje usunąć go i tak przy
	// zakończeniu testu :)

	// if (daoMock) // grrr^2...
	// 	delete daoMock;
}

TEST_F(DaoFactoryTests, throwsLogicErrorWhenDaoIsRegisteredTwice)
{
	daoFactory.registerDao("someDao", []() -> Dao::UnknownDaoPtr
		{ return std::make_unique<SomeDummyDao>(); });

	try
	{
		daoFactory.registerDao("someDao", []() -> Dao::UnknownDaoPtr
			{ return std::make_unique<SomeDummyDao>(); });

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
	daoFactory.registerDao("someDao", []() -> Dao::UnknownDaoPtr
		{ return std::make_unique<SomeDummyDao>(); });

	// IDummyDao* unknownDao = new SomeDummyDao();
	// IOtherDummyDao* otherDao = dynamic_cast<IOtherDummyDao*>(unknownDao);

	try
	{
		auto someDao = daoFactory.createDao<IOtherDummyDao>("someDao");
		// someDao->bar();
		FAIL() << "Expected logic error";
	}
	catch(LogicError& err)
	{
		auto expected = "DaoFactory: trying to cast someDao to wrong type";
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
