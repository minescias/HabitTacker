#include <gmock/gmock.h>

#include <Core/Cli/Parameters.h>
#include <Core/Cli/Validator.h>
#include <Core/Exceptions/RuntimeError.h>

namespace Tests
{

using namespace testing;

class ValidatorTests : public testing::Test
{
public:
	ValidatorTests(){};


	void testForError(const char* errorMessage)
	{
		try
		{
			validator.validate(parameters);
			FAIL() << "expected runtime error";
		}
		catch (RuntimeError& err)
		{
			auto expected = "-foo is not defined";
			ASSERT_STREQ(err.what(), errorMessage);
		}
	}

	void testForPass()
	{
		try
		{
			validator.validate(parameters);
		}
		catch (RuntimeError& err)
		{
			FAIL() << err.what();
		}
	}

	Cli::Parameters parameters;
	Cli::Validator validator;
};


// basic validation, checks param existance
TEST_F(ValidatorTests, require_empty_params_passes_when_params_is_empty)
{
	testForPass();
}

TEST_F(ValidatorTests, throws_error_on_unknown_flag)
{
	parameters.setFlag("foo");
	
	testForError("-foo is not defined");
}

TEST_F(ValidatorTests, throws_error_on_unknown_parameter)
{
	parameters.setParameter("bar", "123");

	testForError("-bar is not defined");
}

TEST_F(ValidatorTests, passes_when_argument_is_not_set)
{
	validator.addParam("foo");

	testForPass();
}
//TODO: Połączenie tych dwóch testów?
TEST_F(ValidatorTests, passes_when_argument_is_set)
{
	validator.addParam("foo");
	validator.addParam("bar").type(Cli::ParamType::Integer);
	
	parameters.setFlag("foo");
	parameters.setParameter("bar", "123");

	testForPass();
}

// required parameter
TEST_F(ValidatorTests, throws_error_when_required_parameter_is_not_set)
{
	validator.addParam("foo").required();
	testForError("Missing required parameter '-foo'");

	parameters.setFlag("foo");
	testForPass();
}

// type validation
TEST_F(ValidatorTests, passes_when_types_are_correct)
{
	// This test passed without any change in Validator class.
	// It was added to make sure that I won't break anything later on

	validator.addParam("flag"); 
	validator.addParam("foo").type(Cli::ParamType::Integer);
	validator.addParam("bar").type(Cli::ParamType::Double);
	validator.addParam("aaa").type(Cli::ParamType::String);

	parameters.setFlag("flag");
	parameters.setParameter("foo", "123");
	parameters.setParameter("bar", "1.23");
	parameters.setParameter("aaa", "razdwatrzy");

	testForPass();
}

TEST_F(ValidatorTests, throws_error_when_bolean_type_doesnt_match)
{
	validator.addParam("flag"); // boolean by default
	parameters.setParameter("flag", "aaa");
	
	testForError("Parameter 'flag' does not require any value");
}

TEST_F(ValidatorTests, non_boolean_parameters_requires_a_value)
{
	validator.addParam("foo").type(Cli::ParamType::Integer);
	parameters.setFlag("foo");
	
	testForError("Parameter 'foo' requires a value");
}

TEST_F(ValidatorTests, throws_error_when_integer_type_doesnt_match)
{
	validator.addParam("foo").type(Cli::ParamType::Integer);
	parameters.setParameter("foo", "xyz");
	
	testForError("Cannot read value 'xyz' of parameter 'foo' as number");
}

TEST_F(ValidatorTests, throws_error_when_double_type_doesnt_match)
{
	validator.addParam("foo").type(Cli::ParamType::Double);
	parameters.setParameter("foo", "xyz");
	
	testForError("Cannot read value 'xyz' of parameter 'foo' as real number");	
}

} // namespace Tests
