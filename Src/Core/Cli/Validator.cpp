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

	checkRequired(parameters);
}

ParamProperties& Validator::addParam(const std::string& name)
{
	// std::map::emplace() returns std::pair<iterator,bool>...
	// that's why i had to do that strange .first->second thing
	return registeredParams.emplace(name, ParamProperties()).first->second;
}

void Validator::checkParam(const std::string& name)
{
	for (const auto& param: registeredParams)
	{
		if (param.first == name)
			return;
	}	

	throw RuntimeError("-" + name + " is not defined");
}

void Validator::checkRequired(const Parameters& parameters)
{
	for (const auto& param: registeredParams)
	{
		if (param.second.isRequired())
			checkRequired(parameters, param.first);
	}	
}

void Validator::checkRequired(const Parameters& parameters, const std::string& name)
{
	for (const auto& flag: parameters.getAllFlags())
	{
		if (name == flag)
			return;	
	}

	for (const auto& userParam: parameters.getAllArguments())
	{
		if (name == userParam.first)
			return;	
	}

	throw RuntimeError("Missing required parameter '-" + name + "'");
}

} // namespace Cli
