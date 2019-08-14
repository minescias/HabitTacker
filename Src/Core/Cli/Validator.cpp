#include "Core/Cli/Validator.h"

#include <Core/DateTime/DateLiteral.h>
#include <Core/Exceptions/RuntimeError.h>

namespace Cli
{

Validator::Validator()
	: filterEnabled(false)
{
}

void Validator::validate(Parameters& parameters)
{
	for (const auto& flag: parameters.getAllFlags())
		checkParam(flag, "");
	
	for (const auto& param: parameters.getAllArguments())
		checkParam(param.first, param.second);

	checkRequired(parameters);
	checkFilter(parameters);
}

ParamProperties& Validator::addParam(const std::string& name)
{
	// std::map::emplace() returns std::pair<iterator,bool>...
	// that's why i had to do that strange .first->second thing
	return registeredParams.emplace(name, ParamProperties()).first->second;
}

void Validator::enableFilter()
{
	filterEnabled = true;
}

void Validator::checkParam(const std::string& name, const std::string& value)
{
	for (const auto& param: registeredParams)
	{
		if (param.first == name)
		{
			checkType(param.second.getType(), name, value);
			return;
		}
	}

	throw RuntimeError("-" + name + " is not defined");
}

void Validator::checkType(ParamType type, const std::string& name,  const std::string& value)
{
	if (type == ParamType::Boolean)
	{
		if (value.empty())
			return;
		else
			throw RuntimeError("Parameter '" + name + "' does not require any value");
	}

	if (value.empty())
		throw RuntimeError("Parameter '" + name + "' requires a value");

	if (type == ParamType::Integer)
	{
		try
		{
			stoi(value);
		}
		catch (std::invalid_argument& err)
		{
			throw RuntimeError("Cannot read value '" + value + "' of parameter '"
				+ name + "' as number");
		}
	}

	if (type == ParamType::Double)
	{
		try
		{
			stod(value);
		}
		catch (std::invalid_argument& err)
		{
			throw RuntimeError("Cannot read value '" + value + "' of parameter '"
				+ name + "' as real number");
		}
	}

	if (type == ParamType::Date)
	{
		try
		{
			Dt::DateLiteral().parse(value);
			// DateTime::DateTime(const std::string& dateString)
		}
		catch (RuntimeError& err)
		{
			throw RuntimeError("Cannot read value '" + value + "' of parameter '"
				+ name + "' as date");
		}
	}
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

void Validator::checkFilter(const Parameters& parameters)
{
	if (filterEnabled && parameters.getFilter().empty())
		throw RuntimeError("No filter specified");

	if (!filterEnabled && !parameters.getFilter().empty())
		throw RuntimeError("Filter cannot be used with this command");
}

} // namespace Cli
