#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Tests/Tools/CreateTestDirectory.h"

int main(int argc, char* argv[])
{
	Tests::createTestDirectory();
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
