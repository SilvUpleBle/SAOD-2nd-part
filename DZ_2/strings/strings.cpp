#include <iostream>
#include "utils2.h"
using namespace std;


int main()
{
	char str[] = "Hello!";
	cout << str << endl;

	cout << strlen(str) << " " << sizeof(str) << " " << utils2::len(str) << endl;

	char t[32];
	utils2::copy(str, t);

	cout << utils2::compare(str, t);
}