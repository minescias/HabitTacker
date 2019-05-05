#include <gmock/gmock.h>

#include "HT/Dao/DaoFactory.h"
#include "HT/Dao/UnknownDao.h"

using namespace testing;

namespace Tests
{

class IDummyDao : public Dao::UnknownDao
{
public:
	virtual int foo() = 0;
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

class SomeOtherDao : public Dao::UnknownDao
{
public:
	SomeOtherDao(){}
	int foo(){return 3423;}
};

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

// TEST_F(DaoFactoryTests, allowsToRegisterAndGetDaoMock)
// {
// 	daoFactory.registerDao("someDao", []() -> Dao::UnknownDaoPtr
// 	{
// 		auto daoMock = std::make_unique<DummmyDaoMock>();
// 		EXPECT_CALL(*daoMock, foo()).WillOnce(Return(9786));

// 		return daoMock; //static_cast<UnknownDao*>(daoMock.release()));
// 	}
// 	);

// 	auto someDao = daoFactory.createDao<IDummyDao>("someDao");
// }

} // namespace Tests