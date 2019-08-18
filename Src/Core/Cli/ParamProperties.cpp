#include "Core/Cli/ParamProperties.h"

namespace Cli
{

ParamProperties::ParamProperties()
	: _type(ParamType::Boolean)
	, _requirementLevel(RequirementLevel::Optional)
{
}

ParamProperties& ParamProperties::requirement(RequirementLevel level) 
{
	_requirementLevel = level;
	return *this;	
}

ParamProperties& ParamProperties::type(ParamType type)
{
	_type = type;
	return *this;
}

ParamProperties& ParamProperties::errorMessage(const std::string& message)
{
	_errorMessage = message;
	return *this;
}

RequirementLevel ParamProperties::getRequirement() const 
{
	return _requirementLevel;
}

ParamType ParamProperties::getType() const
{
	return _type;
}

std::string ParamProperties::getErrorMessage() const
{
	return _errorMessage;
}

} // namespace Cli
