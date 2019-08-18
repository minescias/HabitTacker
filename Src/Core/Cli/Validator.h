#ifndef __VALIDATOR_H
#define __VALIDATOR_H

#include <vector>

#include <Core/Cli/Parameters.h>

namespace Cli
{

enum class ParamType
{
	Boolean,
	Integer,
	Double,
	String,
	Date
};

enum class RequirementLevel
{
	Forbidden,
	Optional,
	Required
};

class ParamProperties
{
public:
	ParamProperties()
		: _type(ParamType::Boolean)
		, _requirementLevel(RequirementLevel::Optional)
	{}

	ParamProperties& requirement(RequirementLevel level) 
	{
		_requirementLevel = level;
		return *this;	
	}

	ParamProperties& type(ParamType type)
	{
		_type = type;
		return *this;
	}

	ParamProperties& errorMessage(const std::string& message)
	{
		_errorMessage = message;
		return *this;
	}

	RequirementLevel getRequirement() const {return _requirementLevel; }
	ParamType getType() const {return _type; }
	std::string getErrorMessage(){return _errorMessage; }

private:
	RequirementLevel _requirementLevel;
	ParamType _type;
	std::string _errorMessage;
};

class Validator
{
public:
	Validator();

	void validate(const Parameters& parameters);

	ParamProperties& addParam(const std::string& foo);
	ParamProperties& addFilter();
	ParamProperties& addDefaultParameter();

private:
	void checkParam(const std::string& name, const std::string& value);
	void checkType(ParamType type, const std::string& name, const std::string& value);
	void checkRequired(const Parameters& parameters);
	void checkRequired(const Parameters& parameters, const std::string& name);
	void checkFilter(const Parameters& parameters);
	void checkDefaultParameter(const Parameters& parameters);

private:
	std::map<std::string, ParamProperties> registeredParams;
	ParamProperties filter;
	ParamProperties defaultParameter;
};

} // namespace Cli

#endif // __VALIDATOR_H
