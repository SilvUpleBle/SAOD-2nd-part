#include <iostream>
#include "Str.h"
int main()
{
    Str s1("testtest");
    std::cout << s1.rfind("te", 5) << std::endl;
    std::cout << s1.rfind("", 5) << std::endl;
    std::cout << s1.rfind("testtest", 5) << std::endl;
}
