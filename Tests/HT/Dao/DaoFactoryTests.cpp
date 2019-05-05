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

// nie mogę użyć tej wersji ponieważ release jest metodą nie constową a z
// jakiegoś powodu nie mogę używać constowych metod w dao :(
// template<typename T>
// Dao::DaoCreatorFunc createDaoMock(std::unique_ptr<T> daoPtr)
// {
// 	return [&daoPtr2 = std::move(daoPtr)]() -> Dao::UnknownDaoPtr
// 	{
// 		auto unknownDaoPtr = dynamic_cast<Dao::UnknownDao*>(daoPtr2.release());
// 		return std::unique_ptr<Dao::UnknownDao>(unknownDaoPtr);
// 	};
// }

template<typename T>
Dao::DaoCreatorFunc createDaoMock(T* daoPtr)
{
	return [daoPtr]() -> Dao::UnknownDaoPtr
	{
		auto unknownDaoPtr = dynamic_cast<Dao::UnknownDao*>(daoPtr);
		return std::unique_ptr<Dao::UnknownDao>(unknownDaoPtr);
	};
}

TEST_F(DaoFactoryTests, allowsToRegisterAndGetDaoMock)
{
	auto daoMock = new DummmyDaoMock(); //grrr...
	EXPECT_CALL(*daoMock, foo()).WillOnce(Return(9786));

	daoFactory.registerDao("someDao", createDaoMock(daoMock));

	// jeśli dao nigdy nie zostanie utworzone to nie będzie uniqie_ptr, który
	// usunąłby później to co jest pod wskaźnikiem - wyciek pamięci, dlatego
	// muszę robić to ręcznie tutaj
	if (daoMock) // grrr^2...
		delete daoMock;

	auto someDao = daoFactory.createDao<IDummyDao>("someDao");
	ASSERT_EQ(someDao->foo(), 9786);
}

} // namespace Tests
