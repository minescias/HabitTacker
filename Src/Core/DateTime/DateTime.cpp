#include "Core/DateTime/DateTime.h"

#include <regex>

#include "Core/DateTime/DateConsts.h"
#include "Core/Utils/Exceptions/RuntimeError.h"

// dateTime format DD-MM-YYYY

namespace
{

std::string formatNumber(int value, int length)
{
	auto result = std::to_string(value);

	if (result.length() < length)
		result = std::string(length - result.length(), '0') + result;

	return result;
}

} // namespace

namespace Dt
{

DateTime::DateTime(const std::string& dateString)
{
	if (!validateDateStringFormat(dateString))
		throw RuntimeError(getErrorMessage(dateString));

	auto tm = std::tm();
	tm.tm_mday = stoi(dateString.substr(0, 2));
	tm.tm_mon = stoi(dateString.substr(3, 2)) - 1;
	tm.tm_year = stoi(dateString.substr(6, 4)) - 1900;

	tm.tm_sec = 0;
	tm.tm_min = 0;
	tm.tm_hour = 0;

	if (!validateDateValues(tm))
		throw RuntimeError(getErrorMessage(dateString));

	timestamp = std::mktime(&tm) - timezone;
}

DateTime::DateTime(Timestamp timestamp)
	: timestamp(timestamp)
{
}

Timestamp DateTime::unixTime() const
{
	return timestamp;
}

std::string DateTime::dateString() const
{
	// tm to wskaźnik. Nie ma tutaj wycieku pamięci?
	auto tm = std::localtime(&timestamp);
	std::string output = "";

	output += formatNumber(tm->tm_mday, 2) + "-"
		+ formatNumber(tm->tm_mon + 1, 2) + "-"
		+ std::to_string(tm->tm_year + 1900);

	// delete tm

	return output;
}

int DateTime::weekDay() const
{
	// nr dnia tygodnia odpowiada temu z std::tm
	return std::localtime(&timestamp)->tm_wday; // thread unsafe
}

DateTime& DateTime::addDays(int nrOfDays)
{
	timestamp += secondsInDay * nrOfDays;
	return *this;
}

Duration DateTime::operator-(const DateTime& rhs)
{
	return Duration{timestamp - rhs.timestamp};
}

bool DateTime::validateDateStringFormat(const std::string& dateString) const
{
	auto regex = std::regex(R"r(\d{2}-\d{2}-\d{4})r");
	auto match = std::cmatch();

	return std::regex_match(dateString.c_str(), match, regex);
}

bool DateTime::validateDateValues(const std::tm& tm) const
{
	return
		1 <= tm.tm_mday && tm.tm_mday <=31
		&& 0 <= tm.tm_mon && tm.tm_mon <=11;
}

std::string DateTime::getErrorMessage(const std::string& dateString) const
{
	return "Cannot convert '" + dateString + "' to date. "
		"Expected date format is DD-MM-YYYY";
}

} // namespace Dt


