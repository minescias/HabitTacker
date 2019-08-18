#ifndef __VALIDATOR_H
#define __VALIDATOR_H

#include <vector>

#include <Core/Cli/Parameters.h>
#include <Core/Cli/ParamProperties.h>

namespace Cli
{

class Validator
{
public:
	Validator();

	ParamProperties& addParam(const std::string& foo);
	ParamProperties& addFilter();
	ParamProperties& addDefaultParameter();

	void validate(const Parameters& parameters);

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
