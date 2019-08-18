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
		return  *this;
	}

	RequirementLevel getRequirement() const {return _requirementLevel; }
	ParamType getType() const {return _type; }

private:
	RequirementLevel _requirementLevel;
	ParamType _type;
};

class Validator
{
public:
	Validator();

	void validate(const Parameters& parameters);

	ParamProperties& addParam(const std::string& foo);
	ParamProperties& addFilter();

private:
	void checkParam(const std::string& name, const std::string& value);
	void checkType(ParamType type, const std::string& name, const std::string& value);
	void checkRequired(const Parameters& parameters);
	void checkRequired(const Parameters& parameters, const std::string& name);
	void checkFilter(const Parameters& parameters);

private:
	std::map<std::string, ParamProperties> registeredParams;
	ParamProperties filter;
};

} // namespace Cli

#endif // __VALIDATOR_H
