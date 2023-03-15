#include <iostream>
#include "Test.h"
#include "Child.h"
#include "Aggregate.h"
#include "AggregateT.h"

void foo1()
{
    Test t1; 
    std::cout << "\n-exiting from foo1-\n\n";

}

void foo2(Test* p)
{
    Test* p2 = p;
    delete p2;
    std::cout << "\n-exiting from foo2-\n";
}

int main()
{
    std::cout << "-foo1 is running-\n\n";
    foo1();
    std::cout << "\n-foo1 is end-\n\n\n";

    std::cout << "-foo2 is running-\n\n";
    Test* p = new Test;
    foo2(p);
    std::cout << "\n-foo2 is end-\n\n\n";


    Child s1;
    Aggregate A1;
    AggregateT<Test> ATT;
    AggregateT<Child> AT;
}

