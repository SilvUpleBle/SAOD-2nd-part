#include <iostream>
#include <set>
#include <list>
#include "Test.h"

int main()
{
	std::list<Test> ls;
	ls.push_back(Test());
	ls.push_back(Test());
	ls.push_back(Test());
	std::cout << "list size before remove: " << ls.size() << std::endl;
	ls.sort();

	ls.remove(Test());
	std::cout << "list size after remove: " << ls.size() << std::endl;

	std::set<Test> st;
	st.insert(Test());
	st.insert(Test());
	std::cout << "set size: " << st.size() << std::endl;
}