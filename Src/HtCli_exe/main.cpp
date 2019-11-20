#include "HtCli/AppInit.h"

#include "Tests/Tools/CreateTestDirectory.h"

int main(int argc, char* argv[])
{
	Tests::createTestDirectory();
	return appInit(argc, argv);
}
