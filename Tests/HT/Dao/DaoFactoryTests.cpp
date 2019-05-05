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

template<typename T>
Dao::DaoCreatorFunc createDaoMock(std::unique_ptr<T> daoPtr)
{
	return [&daoPtr = std::move(daoPtr)]() -> Dao::UnknownDaoPtr
	{
		auto unknownDaoPtr = dynamic_cast<Dao::UnknownDao*>(daoPtr.release());
		return std::unique_ptr<Dao::UnknownDao>(unknownDaoPtr);
	};
}

// TEST_F(DaoFactoryTests, allowsToRegisterAndGetDaoMock)
// {
// 	std::unique_ptr<DummmyDaoMock> daoMock = std::make_unique<DummmyDaoMock>();
// 	EXPECT_CALL(*daoMock, foo()).WillOnce(Return(9786));

// 	daoFactory.registerDao("someDao", createDaoMock(std::move(daoMock)));

// 	auto someDao = daoFactory.createDao<IDummyDao>("someDao");
// 	ASSERT_EQ(someDao->foo(), 9786);
// }

} // namespace Tests