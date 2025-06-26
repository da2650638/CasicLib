#pragma once

#include <format>
#include <iostream>
#include <source_location>
#include <cstdint>

// NOTE: 小知识，函数模板和成员函数自带inline修饰，所以不会出现ODR风险和优化意义的inline不一样( __attribute__((always_inline)) )， C++的inline仅仅只是使得符号复合单一定义原则

#define FOREACH_LOG_LEVEL(CASE)	\
	CASE(trace)		\
	CASE(debug)		\
	CASE(info)		\
	CASE(warning)	\
	CASE(error)		\
	CASE(fatal)	

namespace casic
{
namespace minilog
{

	enum class log_level : std::uint8_t 
	{
	#define ENUM(name) name,
		FOREACH_LOG_LEVEL(ENUM)
	#undef ENUM
	};

	inline const char* log_level_to_string(log_level level)
	{
		switch (level) {
	#define CASE(level) case log_level::level: return #level;
			FOREACH_LOG_LEVEL(CASE)
	#undef CASE
		}
		return "unknown";
	}

	inline log_level log_level_from_string(std::string level_string)
	{
#define IF(name) if (level_string == #name) { return log_level::name; }
			FOREACH_LOG_LEVEL(IF)
#undef IF
		return log_level::info;
	}

	// NOTE: std::underlying_type_t<log_level> 获取枚举的本质类型

	// NOTE: 这段代码给我背下来
	template <typename T>
	struct with_source_location {
	private:
		T inner;
		std::source_location loc;
	public:
		// TODO: 搞清楚这段代码的原理
		template <typename U> requires std::constructible_from<T, U>
		consteval/* 代表纯编译期调用的构造函数 */ with_source_location(U&& inner_arg, std::source_location loc = std::source_location::current())
			: inner(std::forward<U>(inner_arg)), loc(std::move(loc)) {}
		constexpr T const& format() const { return inner; }
		constexpr std::source_location const& location() const { return loc; }
	};

	// NOTE: static-inilization技巧
	inline log_level max_level = []() -> log_level {
		// NOTE: define _CRT_SECURE_NO_WARNINGS macro
		auto level = std::getenv("CASIC_MINILOG");
		if (level) {
			return log_level_from_string(level);
		}
		return log_level::info;
	}();

	template <typename... Args>
	void generic_log(log_level level, with_source_location<std::format_string<Args...>> fmt, Args&&... args)
	{
		if (level >= max_level) {
			auto loc = fmt.location();
			std::cout << loc.file_name() << ":" << loc.line() << " [" << log_level_to_string(level) << "] " << std::vformat(fmt.format().get(), std::make_format_args(args...)) << "\n";
		}
	}

#define LOG_FUNCTION(level_name) \
template <typename... Args>	\
void log_##level_name(with_source_location<std::format_string<Args...>> fmt, Args&&... args)	{	\
	generic_log(log_level::level_name, std::move(fmt), std::forward<Args>(args)...);	\
}
	FOREACH_LOG_LEVEL(LOG_FUNCTION)
#undef LOG_FUNCTION
}
}

// NOTE: C语言的特性，自动把引号缝合起来
#define CASIC_MINILOG_P(x) ::casic::minilog::log_info(#x "={}", x);

#undef FOREACH_LOG_LEVEL

