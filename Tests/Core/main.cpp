#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Core/Logger/Log.h>
#include <Core/Logger/Logger.h>

int main(int argc, char* argv[])
{
	// auto logConfig = std::make_unique<Log::Config>();
	// logConfig->enabled = true;
	// logConfig->levels = {Log::Levels::Error, Log::Levels::Sql};
	// auto logger = std::make_unique<Log::Logger>(std::move(logConfig));
	// Log::setLogger(logger.get());

	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}