#pragma once

#include <chrono>
#include <iomanip>
#include <set>
#include <string_view>
#include <vector>
#include <map>
#include <set>
#include <iostream>

namespace Casic 
{

	struct ScopeProfiler
	{
		using ClockType = std::chrono::high_resolution_clock;
		struct Record {
			const char* tag;
			int us;
		};
	private:
		inline thread_local static std::vector<Record> records;
		const char* tag;
		ClockType::time_point beg;
		ClockType::time_point end;

		inline ScopeProfiler(const char* tag, ClockType::time_point beg) : tag(tag), beg(beg) {}
		inline void onDestroy(ClockType::time_point end)
		{
			auto duration = end - beg;
			int us = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
			records.push_back({ tag, us });
		}

	public:
		ScopeProfiler(const char* tag) : ScopeProfiler(tag, ClockType::now()){}
		~ScopeProfiler() { onDestroy(ClockType::now()); }

		inline static const std::vector<Record>& getRecords()
		{
			return records;
		}
		inline static void printlog(std::ostream& out = std::cout)
		{
			if (records.size() == 0) return;
			// TODO: 
		}
	};

}