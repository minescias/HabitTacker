#ifndef __VALIDATOR_H
#define __VALIDATOR_H

#include <vector>

#include <Core/Cli/Parameters.h>

namespace Cli
{

class ParamProperties
{
public:
	ParamProperties()
	{}

	ParamProperties& required() 
	{
		_required = true;
		return *this;	
	}

	bool isRequired() const {return _required; }

private:
	bool _required;
};

class Validator
{
public:
	Validator();

	void validate(Parameters& parameters);

	ParamProperties& addParam(const std::string& foo);

private:
	void checkParam(const std::string& name);
	void checkRequired(const Parameters& parameters);
	void checkRequired(const Parameters& parameters, const std::string& name);

private:
	std::map<std::string, ParamProperties> registeredParams;
};

} // namespace Cli

#endif // __VALIDATOR_H
