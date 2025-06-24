#pragma once
#include "CasicMiniLog.h"

inline void testMiniLog()
{
	// NOTE: 不同的编译器针对参数或{}是否越界可能有不同的行为
	auto s = std::format("1 Hello {3} {2} {1} {0}", 1, 2, 3, 4);
	std::cout << s << "\n";

	// NOTE: 4对应占位数，默认靠右对齐
	s = std::format("2 Hello{:4d}",42);
	std::cout << s << "\n";

	// NOTE: 当占位符未被填充满时用0填充，位数为4，默认靠右对齐
	s = std::format("3 Hello{:04d}", 42);
	std::cout << s << "\n";

	// NOTE: 位数为4，默认靠右对齐，十六进制
	s = std::format("4 Hello{:4x}", 42);
	std::cout << s << "\n";

	// NOTE: 4对应占位数，左对齐，0补位
	s = std::format("5 Hello{:-<4d}", 42);
	std::cout << s << "\n";

	// NOTE: 4对应占位数，右对齐
	s = std::format("6 Hello{:>4d}", 42);
	std::cout << s << "\n";

	// NOTE: 4对应占位数，正号打印出来
	s = std::format("7 Hello{:+4d}", -42);

	// NOTE: 4对应占位数，负号打印出来
	s = std::format("7 Hello{:-4d}", -42);
	std::cout << s << "\n";

	// NOTE: 6对应占位数,默认靠右对齐，当使用十六进制（x）时候#可以将0x（也算到占位数当中）打印出来
	s = std::format("8 Hello{:#6x}", 42);
	std::cout << s << "\n";

	// NOTE: 4对应占位数,>使得靠右对齐，&作为填充个，#打印出0x，冒号前面的数量可变参数列表的id，例如下面的1代表参数16，第1个（从0开始计数）参数，
	s = std::format("9 Hello{2:&>#4x}", 42, 16, 15);
	std::cout << s << "\n";

	// NOTE: 打印浮点数时，.后面的5代表保留几位小数，.前面的10代表整个数的对齐量(包括小数点)，>代表右对齐，&代表占位符，+代表保留+号
	s = std::format("10 Hello{0:&>+10.5f}", 3.14);
	std::cout << s << "\n";

	// NOTE: 括号嵌套，本例子中是代表从外部指定保留多少位（n=4位）小数，注意不可以使用参数id，否则会引发异常(MSVC编译器是这样的，别的暂时不清楚)。
	int n = 4;
	s = std::format("11 Hello[{:10.{}f}]", 3.14, n);
	std::cout << s << "\n";

	// NOTE: 对齐量=10，保留小数点后2位，^代表居中
	s = std::format("12 Hello[{:^10.2f}]", 3.14);
	std::cout << s << "\n";

	// NOTE: 对齐量=9，字符串保留前5个字符，^代表居中
	s = std::format("13 Hello[{:^9.5s}]", "abcdefg");
	std::cout << s << "\n";

	// NOTE: 对齐量=9，默认保留全部字符串
	s = std::format("14 Hello[{:^9s}]", "abcdefg");
	std::cout << s << "\n";

	// NOTE: 对齐量=9，默认保留全部字符串，通过变量n传入保留的字符数量
	n = 3;
	s = std::format("15 Hello[{:^9.{}s}]", "abcdefg", n);
	std::cout << s << "\n";
}