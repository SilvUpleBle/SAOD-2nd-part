#include <iostream>
#include <memory>
#include "Test.h"

std::weak_ptr<Test> wp;

int main()
{
	{
		auto sp = std::shared_ptr<Test>(new Test());
		std::cout << sp.use_count() << std::endl;
		wp = sp;
		std::cout << sp.use_count() << std::endl;
		auto p = wp.lock();
		if (p) {
			std::cout << "object is alive, " << sp.use_count() << std::endl;
		}
		else {
			std::cout << "no owing object" << std::endl;
		}
	}
	auto p = wp.lock();
	if (p) {
		std::cout << "object is alive" << std::endl;
	}
	else {
		std::cout << "no owing object" << std::endl;
	}
}