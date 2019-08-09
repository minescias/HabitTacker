#include <gmock/gmock.h>

#include "Core/Strings/Case.h"

using namespace testing;

class StringsTests : public testing::Test
{
};

TEST_F(StringsTests, changesCaseToLower)
{
    std::string str = "AbCdEf";
    Strings::lower(str);

    ASSERT_THAT(str, Eq("abcdef"));
}

TEST_F(StringsTests, createsNewCopyAndChangesCaseToLower)
{
    const std::string str = "AbCdEf";
    ASSERT_THAT(Strings::lower_copy(str), Eq("abcdef"));
}
