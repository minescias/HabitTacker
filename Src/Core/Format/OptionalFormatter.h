#ifndef __OPTIONAL_FORMATTER_H
#define __OPTIONAL_FORMATTER_H

#include <optional>

template<>
struct fmt::formatter<std::nullopt_t> : formatter<std::string_view>
{
	template<typename FormatContext>
	auto format(std::nullopt_t, FormatContext& ctx)
	{
		return formatter<std::string_view>::format("'null'", ctx);
	}
};

template<typename T>
struct fmt::formatter<std::optional<T>> : formatter<std::string_view>
{
	template<typename ParseContext>
	constexpr auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template<typename FormatContext>
	auto format(std::optional<T> value, FormatContext& ctx)
	{
		if (!value.has_value())
			return format_to(ctx.out(), "{}", "'null'");
		else
			return format_to(ctx.out(), "{}", *value);
	}
};

#endif // __OPTIONAL_FORMATTER_H
