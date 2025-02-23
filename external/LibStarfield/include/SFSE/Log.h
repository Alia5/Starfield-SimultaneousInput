#pragma once

#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <source_location>
#include <utility>

#pragma warning(disable : 26444)

#define SFSE_MAKE_SOURCE_LOGGER(a_func, a_type)                                          \
                                                                                         \
	template <class... Args>                                                             \
	struct [[maybe_unused]] a_func                                                       \
	{                                                                                    \
		a_func() = delete;                                                               \
                                                                                         \
		explicit a_func(                                                                 \
			fmt::format_string<Args...> a_fmt,                                           \
			Args&&... a_args,                                                            \
			std::source_location a_loc = std::source_location::current())                \
		{                                                                                \
			spdlog::log(                                                                 \
				spdlog::source_loc{                                                      \
					a_loc.file_name(),                                                   \
					static_cast<int>(a_loc.line()),                                      \
					a_loc.function_name() },                                             \
				spdlog::level::a_type,                                                   \
				a_fmt,                                                                   \
				std::forward<Args>(a_args)...);                                          \
		}                                                                                \
	};                                                                                   \
                                                                                         \
	template <class... Args>                                                             \
	a_func(fmt::format_string<Args...>, Args&&...) -> a_func<Args...>;

namespace SFSE
{
	namespace log
	{
		SFSE_MAKE_SOURCE_LOGGER(trace, trace);
		SFSE_MAKE_SOURCE_LOGGER(debug, debug);
		SFSE_MAKE_SOURCE_LOGGER(info, info);
		SFSE_MAKE_SOURCE_LOGGER(warn, warn);
		SFSE_MAKE_SOURCE_LOGGER(error, err);
		SFSE_MAKE_SOURCE_LOGGER(critical, critical);
	}

	[[nodiscard]] std::optional<std::filesystem::path> LogDirectory();
}
