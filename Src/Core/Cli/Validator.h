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

class ParamProperties
{
public:
	ParamProperties()
		: _type(ParamType::Boolean)
		, _required(false)
	{}

	ParamProperties& required() 
	{
		_required = true;
		return *this;	
	}

	ParamProperties& type(ParamType type)
	{
		_type = type;
		return  *this;
	}

	bool isRequired() const {return _required; }
	ParamType getType() const {return _type; }

private:
	bool _required;
	ParamType _type;
};

class Validator
{
public:
	Validator();

	void validate(Parameters& parameters);

	ParamProperties& addParam(const std::string& foo);
	void enableFilter();

private:
	void checkParam(const std::string& name, const std::string& value);
	void checkType(ParamType type, const std::string& name, const std::string& value);
	void checkRequired(const Parameters& parameters);
	void checkRequired(const Parameters& parameters, const std::string& name);
	void checkFilter(const Parameters& parameters);

private:
	std::map<std::string, ParamProperties> registeredParams;
	bool filterEnabled;
};

} // namespace Cli

#endif // __VALIDATOR_H
