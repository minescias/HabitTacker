#include <gmock/gmock.h>

#include "Core/DateTime/Duration.h"
#include "Core/DateTime/DateConsts.h"

namespace Tests
{

using namespace testing;

TEST(DurationTest, getNumberOfDays)
{
	EXPECT_THAT(Dt::Duration{Dt::secondsInDay}.getDays(), Eq(1));
	EXPECT_THAT(Dt::Duration{Dt::secondsInDay * 2}.getDays(), Eq(2));
	EXPECT_THAT(Dt::Duration{Dt::secondsInDay * 10}.getDays(), Eq(10));
}

} // namespace Tests
