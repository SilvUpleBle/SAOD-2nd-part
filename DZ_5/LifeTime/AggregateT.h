#pragma once
#include <iostream>
template <typename T>
class AggregateT
{
private:
	T m_objTest;
public:
	AggregateT()
	{
		std::cout << "Create obj AggregateT" << "\n";
	}
	~AggregateT()
	{
		std::cout << "Delete obj AggregateT" << "\n";
	}
};

