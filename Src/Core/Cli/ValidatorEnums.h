#ifndef __VALIDATOR_ENUMS_H
#define __VALIDATOR_ENUMS_H

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

} // namespace Cli

#endif // __VALIDATOR_ENUMS_H
