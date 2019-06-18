#include <gmock/gmock.h>

#include <iostream>
#include <memory>

namespace Tests
{

using namespace testing;

class Foo
{
public:
	Foo() {std::cout << "Foo: constructor\n"; }
	~Foo() {std::cout << "Foo: destruktor\n"; }

	int getInt(){ return 22; };
};

TEST(SmartPtrTests, shared_and_weak_ptr_test)
{
	std::weak_ptr<Foo> weakFoo;
	EXPECT_THAT(weakFoo.use_count(), Eq(0));

	{
		auto foo = std::make_shared<Foo>();
		std::weak_ptr<Foo> weakFoo = foo;

		EXPECT_THAT(foo.use_count(), Eq(1));
		EXPECT_THAT(weakFoo.use_count(), Eq(1));

		// compilation error
		//EXPECT_THAT(weakFoo->getInt(), Eq(22));
		{
			auto foo2 = weakFoo.lock();
			EXPECT_THAT(foo.use_count(), Eq(2));
			EXPECT_THAT(foo2->getInt(), Eq(22));
		}

		EXPECT_THAT(foo.use_count(), Eq(1));
	}

	EXPECT_THAT(weakFoo.use_count(), Eq(0));
}

class Interface
{
public:
	virtual int foo() = 0;
};

class Base : public Interface
{
public:
	virtual int foo(){return 0;};
};

TEST(SmartPtrTests, shared_ptr_and_interfaces)
{
	auto foo = std::make_shared<Base>();
	EXPECT_THAT(foo.use_count(), Eq(1));

	std::shared_ptr<Interface> fooInt =  foo;
	EXPECT_THAT(foo.use_count(), Eq(2));
	EXPECT_THAT(fooInt.use_count(), Eq(2));

}

} // namespace Tests
