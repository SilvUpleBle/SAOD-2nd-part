#pragma once
#include <iostream>
class Test
{
private:
	static int nCount;
public:
	Test()
	{
		std::cout << "create object Test" << "\n";
		nCount++;
		std::cout << "Test nCount = " << nCount << std::endl;
	}
	~Test()
	{
		std::cout << "delete object Test" << "\n";
		nCount--;
		std::cout << "Test nCount = " << nCount << std::endl;
	}
};

