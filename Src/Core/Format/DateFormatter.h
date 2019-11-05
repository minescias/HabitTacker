#ifndef __DATE_FORMATTER_H
#define __DATE_FORMATTER_H

#include <date/date.h>
#include <fmt/format.h>

#include <Core/DateTime/DateFormat.h>

template<>
struct fmt::formatter<date::year_month_day> : formatter<std::string>
{
	template<typename FormatContext>
	auto format(const date::year_month_day& d, FormatContext& ctx)
	{
		auto dateStr = date::format(Dt::conversionDateFormat, d);
		return formatter<std::string>::format(dateStr, ctx);
	}
};

#endif // __DATE_FORMATTER_H
