#ifndef __CLI_TEST_TOOLS_H
#define __CLI_TEST_TOOLS_H

#include <string>
#include <vector>

namespace CLI
{
class App;
}

namespace Tests
{
void parseArguments(CLI::App* app, std::vector<std::string> arguments);

void parseAndThrowError(
	CLI::App* app, std::vector<std::string> arguments, const std::string& errorMsg);

} // namespace Tests

#endif // __CLI_TEST_TOOLS_H
