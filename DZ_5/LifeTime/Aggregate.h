#pragma once
#include "Test.h"
class Aggregate
{
private:
	Test m_objTest;
public:
	Aggregate()
	{
		std::cout << "Create obj Aggregate" << "\n";
	}
	~Aggregate()
	{
		std::cout << "delete obj Aggregate" << "\n";
	}
};

