#pragma once
#include <iostream>

class Test
{
public:
	int Val = 0;
	Test() { std::cout << "test создан" << std::endl;  Val = 0; }
	~Test() { std::cout << "test удалён" << std::endl; }
	
	friend bool operator< (Test const& lhs, Test const& rhs) {
		return lhs.Val < rhs.Val;
	}

	friend bool operator== (Test const& lhs, Test const& rhs) {
		return lhs.Val == rhs.Val;
	}
};

