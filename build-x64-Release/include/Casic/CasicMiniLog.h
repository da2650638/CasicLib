#pragma once

#include <format>
#include <iostream>
#include <source_location>
#include <cstdint>

// NOTE: С֪ʶ������ģ��ͳ�Ա�����Դ�inline���Σ����Բ������ODR���պ��Ż������inline��һ��( __attribute__((always_inline)) )�� C++��inline����ֻ��ʹ�÷��Ÿ��ϵ�һ����ԭ��

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

// NOTE: C���Ե����ԣ��Զ������ŷ������
#define CASIC_MINILOG_P(x) ::casic::minilog::log_info(#x "={}", x);

#undef FOREACH_LOG_LEVEL

