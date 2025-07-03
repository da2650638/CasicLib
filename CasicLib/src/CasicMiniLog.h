#pragma once

#include <format>
#include <iostream>
#include <source_location>
#include <cstdint>
#include <fstream>
#include <chrono>

// NOTE: С֪ʶ������ģ��ͳ�Ա�����Դ�inline���Σ����Բ������ODR���պ��Ż������inline��һ��( __attribute__((always_inline)) )�� C++��inline����ֻ��ʹ�÷��Ÿ��ϵ�һ����ԭ��
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

	// NOTE: std::underlying_type_t<log_level> ��ȡö�ٵı�������

	// NOTE: ��δ�����ұ�����
	template <typename T>
	struct with_source_location {
	private:
		T inner;
		std::source_location loc;
	public:
		// TODO: �������δ����ԭ��
		template <typename U> requires std::constructible_from<T, U>
		consteval/* ���������ڵ��õĹ��캯�� */ with_source_location(U&& inner_arg, std::source_location loc = std::source_location::current())
			: inner(std::forward<U>(inner_arg)), loc(std::move(loc)) {}
		constexpr T const& format() const { return inner; }
		constexpr std::source_location const& location() const { return loc; }
	};

	// NOTE: static-inilization����
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
		// NOTE: ����<<��ԭ�ӵģ����Ƕ��<<���ܻ�����̰߳�ȫ�����⣬����ȹ����ַ�����Ȼ��һ���Դ�ӡ��
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

// NOTE: C���Ե����ԣ��Զ������ŷ������
#define CASIC_MINILOG_P(x) ::casic::minilog::log_info(#x "={}", x);

#undef FOREACH_LOG_LEVEL

