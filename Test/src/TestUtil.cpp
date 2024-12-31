#include "TestUtil.h"

#include <iostream>
#include <optional>
#include <string>
#include <memory>

#include <format>

typedef struct OptionalTestStruct {
	int value;
	OptionalTestStruct(int v)
		: value(v) {}
	void Display() const { std::cout << "TestStruct value: " << value << "\n"; }
}OptionalTestStruct;

void TestOption1()
{
	// 1. Simple Type(int)
	std::optional<int> optInt;
	std::cout << "optInt has value? " << std::boolalpha << optInt.has_value() << "\n";
	optInt = 42;
	if (optInt)
	{
		std::cout << "optInt has value? " << optInt.has_value() << ",value:" << *optInt << std::endl;
	}
	optInt.reset();
	std::cout << "After reset, optInt has value? " << optInt.has_value() << "\n\n";

	// 2.Object type std::string
	std::optional<std::string> optStr("Hello std::optional!");
	if (optStr)
	{
		std::cout << "optStr value: " << *optStr << std::endl;
	}
	optStr = std::nullopt;
	std::cout << "After nullopt, optStr has value? " << optStr.has_value() << "\n\n";

	// 3.Custum struct
	std::optional<OptionalTestStruct> optStruct;
	if (!optStruct)
	{
		std::cout << "optStruct is empty!" << std::endl;
	}
	optStruct.emplace(100);
	if (optStruct)
	{
		optStruct->Display();
	}
	optStruct.reset();
	std::cout << "After reset, optStruct has value? " << optStruct.has_value() << "\n\n";

	// 4.Pointer type
	std::optional<std::unique_ptr<int>> optSmartPtr;
	optSmartPtr = std::make_unique<int>(150);
	if (optSmartPtr)
	{
		std::cout << "optSmartPtr value: " << **optSmartPtr << "\n";
	}
	optSmartPtr.reset();
	std::cout << "After reset, optSmartPtr has value? " << optSmartPtr.has_value() << "\n";

	// 5.
	std::optional<int*> optNewPtr;
	optNewPtr = new int(789);
	if (optNewPtr)
	{
		std::cout << "optNewPtr:" << **optNewPtr << "\n";
	}
	if (optNewPtr) {
		delete* optNewPtr; // Free memory using delete
		optNewPtr.reset(); // Reset optional
	}
	std::cout << "After reset, optNewPtr has value? " << optNewPtr.has_value() << "\n\n";

	// 6.
	std::optional<int*> optMallocPtr;
	optMallocPtr = static_cast<int*>(malloc(sizeof(int)));
	if (optMallocPtr && *optMallocPtr != nullptr)
	{
		**optMallocPtr = 456;
		std::cout << "optMallocPtr value: " << **optMallocPtr << "\n";
	}
	if (optMallocPtr)
	{
		free(*optMallocPtr);
		optMallocPtr = std::nullopt;
	}
	std::cout << "After reset, optMallocPtr has value? " << optMallocPtr.has_value() << "\n";
}
