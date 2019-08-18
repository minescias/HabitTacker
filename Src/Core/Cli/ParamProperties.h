#ifndef __PARAM_PROPERTIES_H
#define __PARAM_PROPERTIES_H

#include <string>

#include <Core/Cli/ValidatorEnums.h>

namespace Cli
{

class ParamProperties
{
public:
	ParamProperties();

	ParamProperties& requirement(RequirementLevel level);
	ParamProperties& type(ParamType type);
	ParamProperties& errorMessage(const std::string& message);

	RequirementLevel getRequirement() const;
	ParamType getType() const;
	std::string getErrorMessage() const;

private:
	RequirementLevel _requirementLevel;
	ParamType _type;
	std::string _errorMessage;
};

} // namespace Cli

#endif // __PARAM_PROPERTIES_H
