#pragma once
#include <iostream>
#include <type_traits>

template <typename _Ty>
constexpr bool is_pod_like_t = std::is_trivial_v<_Ty> && std::is_standard_layout_v<_Ty>;

typedef struct StandardPOD {
	int x;
	float f;
	int* iptr;
}StandardPOD;

typedef struct NonTrivial1 {
	NonTrivial1() {}
}NonTrivial1;

typedef struct NonTrivial2 {
	~NonTrivial2() {}
}NonTrivial2;

typedef struct NonTrivial3 {
	NonTrivial3(const NonTrivial3& other) {}
}NonTrivial3;

typedef struct NonTrivial4 {
	NonTrivial4 operator = (const NonTrivial4& other){ return other; }
}NonTrivial4;

typedef struct ComplexTrivial1 {
	StandardPOD sp;
}ComplexTrivial1;

typedef struct NonComplexTrivial1 {
	NonTrivial1 n1;
}NonComplexTrivial1;

typedef struct StandardLayout1 {
	int x;
	float y;
}StandardLayout1;

typedef struct StandardLayout2 {
	static int s;
}StandardLayout2;

typedef struct NonStandardLayout1 {
	int x;
	float y;
private:
	double d;
}NonStandardLayout1;

typedef struct NonStandartLayout2 {
	virtual void func1() {}
}NonStandartLayout2;

typedef struct StandartLayoutBase1 {
	int x;
}StandartLayoutBase1;

typedef struct StandartLayoutBase2 {
	void func1() {}
	static void func2() {}
}StandartLayoutBase2;

typedef struct StandartLayoutDerive1 : public StandartLayoutBase1 {
	int y;
}StandartLayoutDerive1;

typedef struct StandartLayoutDerive2 : public StandartLayoutBase2 {
	int y;
}StandartLayoutDerive2;

typedef struct StandartLayoutDerive3 : virtual public StandartLayoutBase2 {
	int y;
}StandartLayoutDerive3;

typedef struct StandartLayoutDerive4 : public StandartLayoutBase1, public StandartLayoutBase2 {
	int y;
}StandartLayoutDerive4;

typedef struct StandardLayoutComplex1 {
	StandardLayout1 s1;
	StandardLayout2 s2;
	StandartLayoutBase1 s3;
	StandartLayoutBase2 s4;
}StandardLayoutComplex1;

typedef struct NonStandardLayoutComplex1 {
	NonStandardLayout1 s1;
}NonStandardLayoutComplex1;

inline void TestPod()
{
	std::cout << std::boolalpha;

	std::cout << "int: " << is_pod_like_t<int> << "\n";
	std::cout << "double: " << is_pod_like_t<double> << "\n";

	std::cout << "int*: " << is_pod_like_t<int*> << "\n";

	std::cout << "int&: " << is_pod_like_t<int&> << "\n";
	std::cout << "const int&: " << is_pod_like_t<const int&> << "\n";

	std::cout << "StandardPOD: " << is_pod_like_t<StandardPOD> << "\n";

	std::cout << "ComplexTrivial1: " << is_pod_like_t<ComplexTrivial1> << "\n";
	std::cout << "NonComplexTrivial1: " << is_pod_like_t<NonComplexTrivial1> << "\n";

	std::cout << "NonTrival1: " << is_pod_like_t< NonTrivial1> << "\n";
	std::cout << "NonTrival2: " << is_pod_like_t< NonTrivial2> << "\n";
	std::cout << "NonTrival3: " << is_pod_like_t< NonTrivial3> << "\n";
	std::cout << "NonTrival4: " << is_pod_like_t< NonTrivial4> << "\n";

	std::cout << "StandardLayout1: " << is_pod_like_t< StandardLayout1> << "\n";
	std::cout << "StandardLayout2: " << is_pod_like_t< StandardLayout2> << "\n";
	std::cout << "NonStandardLayout1: " << is_pod_like_t< NonStandardLayout1> << "\n";
	std::cout << "NonStandardLayout2: " << is_pod_like_t< NonStandartLayout2> << "\n";

	std::cout << "StandartLayoutBase1: " << is_pod_like_t< StandartLayoutBase1> << "\n";
	std::cout << "StandartLayoutDerive1: " << is_pod_like_t< StandartLayoutDerive1> << "\n";
	std::cout << "StandartLayoutBase2: " << is_pod_like_t< StandartLayoutBase2> << "\n";
	std::cout << "StandartLayoutDerive2: " << is_pod_like_t< StandartLayoutDerive2> << "\n";
	std::cout << "StandartLayoutDerive3: " << is_pod_like_t< StandartLayoutDerive3> << "\n";
	std::cout << "StandartLayoutDerive4: " << is_pod_like_t< StandartLayoutDerive4> << "\n";

	std::cout << "StandardLayoutComplex1: " << is_pod_like_t< StandardLayoutComplex1> << "\n";
	std::cout << "NonStandardLayoutComplex1: " << is_pod_like_t< NonStandardLayoutComplex1> << "\n";

	std::cout << "std::vector<int>: " << is_pod_like_t<std::vector<int>> << "\n";
}