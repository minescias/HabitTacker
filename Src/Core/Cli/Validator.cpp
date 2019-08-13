#include "Core/Cli/Validator.h"

#include <Core/Exceptions/RuntimeError.h>

namespace Cli
{

Validator::Validator()
{
}

void Validator::validate(Parameters& parameters)
{
	for (const auto& flag: parameters.getAllFlags())
		checkParam(flag);
	
	for (const auto& param: parameters.getAllArguments())
		checkParam(param.first);
}

void Validator::addParam(const std::string& name)
{
	registeredParams.push_back(name);
}

void Validator::checkParam(const std::string& name)
{
	for (const auto& registeredName: registeredParams)
	{
		if (registeredName == name)
			return;
	}	

	throw RuntimeError("-" + name + " is not defined");
}

} // namespace Cli
