#pragma once
#include "Test.h"
class Child : public Test
{
public:
	Child()
	{
		std::cout << "Create obj Child" << "\n";
	}
	~Child()
	{
		std::cout << "delete obj Child" << "\n";
	}
};

