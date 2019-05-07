#include <gmock/gmock.h>

#include <functional>
#include <memory>

using namespace testing;

class LambdaTests : public testing::Test
{
public:
	LambdaTests(){};
};

// unique_ptr
using IntCreator = std::function<std::unique_ptr<int>()>;

auto someFuntion(const IntCreator intCreator)
{
	return intCreator();
}

TEST(LambdaUniqiePtrTests, usingLambdaAsParameter)
{
	auto xx = someFuntion([](){return std::make_unique<int>(5);});

	ASSERT_THAT(*xx, Eq(5));
}

// TEST(LambdaUniqiePtrTests, usingLambdaThatCapturesPointerAsParameter)
// {
// 	FAIL() << "Nie kompiluje się :(";

// Nie działa ponieważ std::function kopiuje obiekty przechwycone przez lambdę,
// a lambda przechwytuje unique_ptr którego nie można skopiować :)

// 	error: use of deleted function
// 	‘Tests::LambdaUniqiePtrTests_usingLambdaThatCapturesPointerAsParameter_Test::TestBody()::<lambda()>::<lambda>(
// 	const Tests::LambdaUniqiePtrTests_usingLambdaThatCapturesPointerAsParameter_Test::TestBody()::<lambda()>&)’
// 		new _Functor(*__source._M_access<_Functor*>());

// 	auto intPtr = std::make_unique<int>(2);

// 	auto xx = someFuntion([intPtr = std::move(intPtr)]()mutable{return std::move(intPtr);});

// 	ASSERT_THAT(*xx, Eq(2));
// }

// shared_ptr
using IntCreatorSh = std::function<std::shared_ptr<int>()>;

auto someFuntionSh(const IntCreatorSh intCreator)
{
	return intCreator();
}

TEST(LambdaSharedPtrTests, usingLambdaAsParameter)
{
	auto xx = someFuntionSh([](){return std::make_shared<int>(5);});

	ASSERT_THAT(*xx, Eq(5));
}

TEST(LambdaSharedPtrTests, usingLambdaThatCapturesPointerAsParameter)
{
	auto intPtr = std::make_shared<int>(2);

	auto xx = someFuntionSh([intPtr](){return intPtr;});

	ASSERT_THAT(*xx, Eq(2));
}
