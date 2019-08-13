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
		ASSERT_NO_THROW(validator.validate(parameters));
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

	ASSERT_NO_THROW(validator.validate(parameters));
}

TEST_F(ValidatorTests, passes_when_argument_is_set)
{
	validator.addParam("foo");
	validator.addParam("bar");
	parameters.setFlag("foo");
	parameters.setParameter("bar", "123");

	ASSERT_NO_THROW(validator.validate(parameters));
}

// required parameter
TEST_F(ValidatorTests, throws_error_when_required_parameter_is_not_set)
{
	validator.addParam("foo").required();
	testForError("Missing required parameter '-foo'");

	parameters.setFlag("foo");
	testForPass();
}

} // namespace Tests
