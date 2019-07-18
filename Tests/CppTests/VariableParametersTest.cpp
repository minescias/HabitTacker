#include <gmock/gmock.h>

#include <iostream>

namespace Tests
{

using namespace testing;

class VariableParametersTest : public testing::Test
{
public:
	VariableParametersTest(){};
};

template<typename T>
void myPrint(T value)
{
	std::cout << value;
}

template<typename T, typename... Targs>
void myPrint (T value, Targs... args)
{
	std::cout << value;
	myPrint(args...);
}

TEST(VariableParameters, simple_test)
{
	auto  expected = "test34.5saf";

	internal::CaptureStdout();
	myPrint("test", "3", "4.5", "saf");

	auto output = testing::internal::GetCapturedStdout();
	ASSERT_STREQ(output.c_str(), expected);
}

} // namespace Tests
