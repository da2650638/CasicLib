#pragma once
#include "CasicMiniLog.h"

inline void testMiniLog()
{
	// NOTE: ��ͬ�ı�������Բ�����{}�Ƿ�Խ������в�ͬ����Ϊ
	auto s = std::format("1 Hello {3} {2} {1} {0}", 1, 2, 3, 4);
	std::cout << s << "\n";

	// NOTE: 4��Ӧռλ����Ĭ�Ͽ��Ҷ���
	s = std::format("2 Hello{:4d}",42);
	std::cout << s << "\n";

	// NOTE: ��ռλ��δ�������ʱ��0��䣬λ��Ϊ4��Ĭ�Ͽ��Ҷ���
	s = std::format("3 Hello{:04d}", 42);
	std::cout << s << "\n";

	// NOTE: λ��Ϊ4��Ĭ�Ͽ��Ҷ��룬ʮ������
	s = std::format("4 Hello{:4x}", 42);
	std::cout << s << "\n";

	// NOTE: 4��Ӧռλ��������룬0��λ
	s = std::format("5 Hello{:-<4d}", 42);
	std::cout << s << "\n";

	// NOTE: 4��Ӧռλ�����Ҷ���
	s = std::format("6 Hello{:>4d}", 42);
	std::cout << s << "\n";

	// NOTE: 4��Ӧռλ�������Ŵ�ӡ����
	s = std::format("7 Hello{:+4d}", -42);

	// NOTE: 4��Ӧռλ�������Ŵ�ӡ����
	s = std::format("7 Hello{:-4d}", -42);
	std::cout << s << "\n";

	// NOTE: 6��Ӧռλ��,Ĭ�Ͽ��Ҷ��룬��ʹ��ʮ�����ƣ�x��ʱ��#���Խ�0x��Ҳ�㵽ռλ�����У���ӡ����
	s = std::format("8 Hello{:#6x}", 42);
	std::cout << s << "\n";

	// NOTE: 4��Ӧռλ��,>ʹ�ÿ��Ҷ��룬&��Ϊ������#��ӡ��0x��ð��ǰ��������ɱ�����б��id�����������1�������16����1������0��ʼ������������
	s = std::format("9 Hello{2:&>#4x}", 42, 16, 15);
	std::cout << s << "\n";

	// NOTE: ��ӡ������ʱ��.�����5��������λС����.ǰ���10�����������Ķ�����(����С����)��>�����Ҷ��룬&����ռλ����+������+��
	s = std::format("10 Hello{0:&>+10.5f}", 3.14);
	std::cout << s << "\n";

	// NOTE: ����Ƕ�ף����������Ǵ�����ⲿָ����������λ��n=4λ��С����ע�ⲻ����ʹ�ò���id������������쳣(MSVC�������������ģ������ʱ�����)��
	int n = 4;
	s = std::format("11 Hello[{:10.{}f}]", 3.14, n);
	std::cout << s << "\n";

	// NOTE: ������=10������С�����2λ��^�������
	s = std::format("12 Hello[{:^10.2f}]", 3.14);
	std::cout << s << "\n";

	// NOTE: ������=9���ַ�������ǰ5���ַ���^�������
	s = std::format("13 Hello[{:^9.5s}]", "abcdefg");
	std::cout << s << "\n";

	// NOTE: ������=9��Ĭ�ϱ���ȫ���ַ���
	s = std::format("14 Hello[{:^9s}]", "abcdefg");
	std::cout << s << "\n";

	// NOTE: ������=9��Ĭ�ϱ���ȫ���ַ�����ͨ������n���뱣�����ַ�����
	n = 3;
	s = std::format("15 Hello[{:^9.{}s}]", "abcdefg", n);
	std::cout << s << "\n";
}