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

TEST_F(LogTests, do_not_log_when_no_logger_is_set)
{
	auto output = runTests("shfksjldf");
	ASSERT_TRUE(output.empty());
}

TEST_F(LogTests, log_simple_string_as_common)
{
	auto expected = "Jakiś tam tekst do zalogowania\n";

	setLogger({Log::Levels::Common});
	auto output = runTests("Jakiś tam tekst do zalogowania");
	ASSERT_THAT(output, Eq(expected));
}

TEST_F(LogTests, does_not_log_text_with_different_level_than_enabled)
{
	setLogger({Log::Levels::Common});

	internal::CaptureStdout();
	log(Log::Levels::Error, "Jakiś tam tekst do zalogowania");
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_TRUE(output.empty());
}

TEST_F(LogTests, log_text_with_correct_level)
{
	auto expected = "Jakiś tam tekst do zalogowania\n";
	setLogger({Log::Levels::Error});

	internal::CaptureStdout();
	log(Log::Levels::Error, "Jakiś tam tekst do zalogowania");
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_THAT(output, Eq(expected));
}

TEST_F(LogTests, log_text_with_parametr)
{
	auto expected = "Błąd w linii 42\n";

	setLogger({Log::Levels::Common});

	internal::CaptureStdout();
	log(Log::Levels::Common, "Błąd w linii {}", 42);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_THAT(output, Eq(expected));
}

TEST_F(LogTests, log_text_with_parametr_using_default_level)
{
	auto expected = "Błąd w linii 42\n";

	setLogger({Log::Levels::Common});

	internal::CaptureStdout();
	log("Błąd w linii {}", 42);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_THAT(output, Eq(expected));
}

} // namespace Tests
