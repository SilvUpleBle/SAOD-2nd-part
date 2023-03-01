#include <iostream>
#include "LList.h"

int main()
{
    LList<int> list;
    list.push_front(2);
    list.push_front(1);
    list.push_front(0);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    for (int i = 0; i < list.get_size(); i++)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    list.remove_at(4);
    list.pop_front();
    list.pop_back();

    for (int i = 0; i < list.get_size(); i++)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    list[0] = 2;
    list[1] = 1;
    list[2] = 0;

    for (int i = 0; i < list.get_size(); i++)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    list.insert(1, 5);
    list.insert(2, 6);

    for (int i = 0; i < list.get_size(); i++)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "size = " << list.get_size() << std::endl;

    std::cout << "front = " << list.front() << std::endl;
    std::cout << "back = " << list.back() << std::endl;

    std::cout << "empty? " << list.empty() << std::endl;
    list.clear();
    std::cout << "empty? " << list.empty() << std::endl;


}