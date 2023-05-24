#pragma once
#include <iostream>

class Test
{
public:
	int Val = 0;
	Test() { std::cout << "test создан" << std::endl;  Val = 0; }
	~Test() { std::cout << "test удалён" << std::endl; }
};

