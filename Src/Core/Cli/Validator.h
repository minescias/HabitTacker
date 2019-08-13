#ifndef __VALIDATOR_H
#define __VALIDATOR_H

#include <vector>

#include <Core/Cli/Parameters.h>

namespace Cli
{

class Validator
{
public:
	Validator();

	void validate(Parameters& parameters);

	void addParam(const std::string& foo);

private:
	void checkParam(const std::string& name);

private:
	std::vector<std::string> registeredParams;
};

} // namespace Cli

#endif // __VALIDATOR_H
