#include <gmock/gmock.h>

#include "Core/Strings/Compare.h"
#include "Core/Exceptions/LogicError.h"

using namespace testing;

class CompareTests : public testing::Test
{
};

TEST_F(CompareTests, StartsWith_throwsErrorWhenSourceIsEmpty)
{
    try
    {
        Strings::startsWith("", "xxx");
        FAIL() << "Logic error should be thrown";
    }
    catch(const LogicError& err)
    {
        std::string expected = "Strings::startsWith: source is empty";
        ASSERT_THAT(err.what(), Eq(expected));
    }
}

TEST_F(CompareTests, StartsWith_returnsTrueIfMatcherIsEmpty)
{
    ASSERT_TRUE(Strings::startsWith("some string", ""));
}

TEST_F(CompareTests, StartsWith_returnsFalseIfBeginningDoesntMatch)
{
    ASSERT_FALSE(Strings::startsWith("some string", "xxx"));
}

TEST_F(CompareTests, StartsWith_returnsTrueIfBeginnignMatches)
{
    ASSERT_TRUE(Strings::startsWith("abcdefgh", "abc"));
}
