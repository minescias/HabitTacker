#include <gmock/gmock.h>

#include <Core/Logger/Log.h>
#include <Core/Logger/Logger.h>

namespace Tests
{
using namespace testing;

class LogTests : public testing::Test
{
public:
	LogTests(){};

	void setLogger(std::set<Log::Levels> levels)
	{
		auto logConfig = std::make_unique<Log::Config>();
		logConfig->enabled = true;
		logConfig->levels = levels;

		logger = std::make_unique<Log::Logger>(std::move(logConfig));
		Log::setLogger(logger.get());
	}

	auto runTests(std::string_view text)
	{
		internal::CaptureStdout();
		log("Jakiś tam tekst do zalogowania");
		return testing::internal::GetCapturedStdout();
	}

	std::unique_ptr<Log::Logger> logger;
};

TEST_F(LogTests, doNotLogWhenNoLoggerIsSet)
{
	auto output = runTests("shfksjldf");
	ASSERT_TRUE(output.empty());
}

TEST_F(LogTests, logSimpleStringAsCommon)
{
	auto expected = "Jakiś tam tekst do zalogowania\n";

	setLogger({Log::Levels::Common});
	auto output = runTests("Jakiś tam tekst do zalogowania");
	ASSERT_THAT(output, Eq(expected));
}

TEST_F(LogTests, doesNotLogTextWithDifferentLevel)
{
	setLogger({Log::Levels::Common});

	internal::CaptureStdout();
	log(Log::Levels::Error, "Jakiś tam tekst do zalogowania");
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_TRUE(output.empty());
}

TEST_F(LogTests, logTextWithCorrectLevel)
{
	auto expected = "Jakiś tam tekst do zalogowania\n";
	setLogger({Log::Levels::Error});

	internal::CaptureStdout();
	log(Log::Levels::Error, "Jakiś tam tekst do zalogowania");
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_THAT(output, Eq(expected));
}

} // namespace Tests
