#include <gmock/gmock.h>

namespace Tests
{

using namespace testing;

class Foo
{
public:
	class Iterator
	{	
	public:
		Iterator(int* position) : position(position){}
		int* operator*(){ return position; };
		Iterator& operator++() { position ++; return *this; }
		bool operator!=(const Iterator it) const {return position != it.position; }

	private:
		int* position;
	};

	Foo(int data[5]) { for (int i = 0; i < 5; i++) this->data[i] = data[i]; }

	Iterator begin() { return Iterator(&data[0]); }
	Iterator end() { return Iterator(&data[5]); }

private:
	int data[5];
};

TEST(ForLoopTest, custom_class_iterator_test)
{
	int data[5] = {1,2,3,4,5};
	auto foo = Foo(data);
	auto result = 0;
	auto expected = 15; //sum of data

	for(auto data : foo)
		result = result + *data;

	ASSERT_THAT(result, Eq(expected));
}

} // namespace Tests
