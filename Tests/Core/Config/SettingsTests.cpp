#include <gmock/gmock.h>

#include "Core/Exceptions/RuntimeError.h"

#include "Core/Config/Settings.h"

namespace Tests
{

using namespace testing;

TEST(SettingsTests, readAndWriteSettings)
{
	auto name = "database";
	auto value = "myDatabase";
	auto settings = Config::Settings();
	settings.registerSettings(Config::SettingsMap{{"database", ""}});

	settings.set(name, value);
	ASSERT_STREQ(settings.get(name).c_str(),value);
}

TEST(SettingsTests, throwsRuntimeErrorWhenSettingUntegisteredField)
{
	auto name = "aaaaaaa";
	auto value = "value";
	auto settings = Config::Settings();

	try
	{
		settings.set(name, value);
		FAIL() << "Runtime error expected";
	}
	catch(RuntimeError& err)
	{
		auto expected = "Trying to set unknown setting aaaaaaa";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(SettingsTests, throwsRumtimeErrorWhenGettingUnregisteredSetting)
{
	auto settings = Config::Settings();

	try
	{
		settings.get("bbbbbbb");
		FAIL() << "Runtime error expected";
	}
	catch(RuntimeError& err)
	{
		auto expected = "Trying to get unknown setting bbbbbbb";
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
