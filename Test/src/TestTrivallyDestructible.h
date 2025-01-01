#pragma once

#include <type_traits>
#include <iostream>
#include <vector>

typedef struct Trival {
	int i;
	float f;
	double d;
}Trival;

typedef struct NonTrival {
	~NonTrival()
	{
		std::cout << "What the fuck??\n";
	}
};

struct Base
{
	~Base() {}
};

struct Derived : public Base
{
	
};

struct Complex
{
	NonTrival member;
};

struct HasPointer
{
	int* ptr;
};

struct VirtualDesc
{
	virtual ~VirtualDesc() {}
};

inline void TestTrivallyDestructible()
{
	std::cout << std::boolalpha;
	// Base type
	std::cout << "int: " << std::is_trivially_destructible_v<int> << "\n";
	std::cout << "double: " << std::is_trivially_destructible_v<double> << "\n";

	// Pointer type
	std::cout << "int*: " << std::is_trivially_destructible_v<int*> << "\n";

	// Custom type
	std::cout << "Trival: " << std::is_trivially_destructible_v<Trival> << "\n";
	std::cout << "NonTrival: " << std::is_trivially_destructible_v<NonTrival> << "\n";

	// Base and Derived
	std::cout << "Base: " << std::is_trivially_destructible_v<Base> << "\n";
	std::cout << "Derived: " << std::is_trivially_destructible_v<Derived> << "\n";

	// Complex
	std::cout << "Complex: " << std::is_trivially_destructible_v<Complex> << "\n";

	// HasPointer
	std::cout << "HasPointer: " << std::is_trivially_destructible_v<HasPointer> << "\n";

	// VirtualDesc
	std::cout << "VirtualDesc: " << std::is_trivially_destructible_v<VirtualDesc> << "\n";

	// Container
	std::cout << "std::vector<int>: " << std::is_trivially_destructible_v<std::vector<int>> << "\n";
	std::cout << "std::string: " << std::is_trivially_destructible_v<std::string> << "\n";

	// Reference
	std::cout << "int&: " << std::is_trivially_destructible_v<int&> << "\n";
	std::cout << "const int&: " << std::is_trivially_destructible_v<const int&> << "\n";

	// Void
	std::cout << "void: " << std::is_trivially_destructible_v<void> << "\n";
}