#include <iostream>
#include "utils.h"
typedef unsigned char byte;
using namespace std;


int main()
{
	//int x = 3;
	//int* p = &x;
	//cout << x << ' ' << *p << ' ' << p << endl;

	//p++; 
	//cout << x << ' ' << *p << ' ' << p << endl;
	//cout << p - &x << endl;

	//
	//byte* pb = (byte*)--p;
	//for (byte* pt = pb; pt - pb < sizeof(int); pt++)
	//	cout << (int)*pt << ' ';
	//cout << endl;

	int a = 3;
	int b = 5;
	
	utils::Swap(a, b);

	cout << "a = " << a << endl << "b = " << b << endl;
}