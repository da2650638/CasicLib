#pragma once

#include <format>
#include <iostream>
#include <source_location>
#include <cstdint>
#include <fstream>
#include <chrono>

// NOTE: 小知识，函数模板和成员函数自带inline修饰，所以不会出现ODR风险和优化意义的inline不一样( __attribute__((always_inline)) )， C++的inline仅仅只是使得符号复合单一定义原则
#define FOREACH_LOG_LEVEL(FUNCTION)	\
	FUNCTION(trace)		\
	FUNCTION(debug)		\
	FUNCTION(info)		\
	FUNCTION(warning)	\
	FUNCTION(error)		\
	FUNCTION(fatal)	

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
	inline static log_level s_max_level = []() -> log_level {
		// NOTE: define _CRT_SECURE_NO_WARNINGS macro
		if (auto level = std::getenv("CASIC_MINILOG")) {
			return log_level_from_string(level);
		}
		return log_level::info;
	}();

	inline static std::ofstream s_log_file;

	template <typename... Args>
	void generic_log(log_level level, with_source_location<std::format_string<Args...>> fmt, Args&&... args)
	{
		auto loc = fmt.location();
		auto msg =  std::vformat(fmt.format().get(), std::make_format_args(args...));
		output_log(level, msg, loc);
	}

	inline void set_log_file(const std::string& path) {
		s_log_file = std::ofstream(path, std::ios::app);
	}

	inline void output_log(log_level level, std::string msg, const std::source_location& loc)
	{
		auto now = std::chrono::zoned_time{ std::chrono::current_zone(),
								   std::chrono::system_clock::now() };
		auto finalmsg = std::format("{} {}:{} [{}] {}\n", now, loc.file_name(), loc.line(), log_level_to_string(level), msg);
		// NOTE: 单个<<是原子的，但是多个<<可能会存在线程安全性问题，因此先构造字符串，然后一次性打印。
		if (level >= s_max_level) {
			std::cout << finalmsg;
		}
		if (s_log_file) {
			s_log_file << finalmsg;
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

