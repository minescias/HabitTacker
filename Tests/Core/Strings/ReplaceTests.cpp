#include <gmock/gmock.h>

#include "Core/Strings/Replace.h"

using namespace testing;

class ReplaceTests : public testing::Test
{
};


TEST_F(ReplaceTests, returnsTextWitchoutChangesIfNothingToReplace)
{
    auto source = "Ala ma kota";
    auto expected = "Ala ma kota";

    auto result = Strings::replaceAllCopy(source, "xxx", "yyy");
    EXPECT_THAT(result, Eq(expected));
}

TEST_F(ReplaceTests, replaceSingleOccurenceTest)
{
    auto source = "Ala ma kota";
    auto expected = "Ala miała kota";

    auto result = Strings::replaceAllCopy(source, "ma", "miała");
    EXPECT_THAT(result, Eq(expected));
}

TEST_F(ReplaceTests, replaceMultipleOccurences)
{
    auto source = "Ala ma kota, kot ma mysz";
    auto expected = "Ala miała kota, kot miała mysz"; // :)

    auto result = Strings::replaceAllCopy(source, "ma", "miała");
    EXPECT_THAT(result, Eq(expected));
}

TEST_F(ReplaceTests, replaceWhenFromAndToContainsTheSameText)
{
    auto source = "Ala ma kota, kot ma mysz";
    auto expected = "Ala ma mieć kota, kot ma mieć mysz"; // :)

    auto result = Strings::replaceAllCopy(source, "ma", "ma mieć");
    EXPECT_THAT(result, Eq(expected));
}
