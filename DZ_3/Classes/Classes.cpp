#include <iostream>
#include "Complex.h"

int main()
{
	Complex x[4];
	std::cout << x[0] << x[1] << x[2] << x[3];

	std::cout << std::endl;

	Complex v[4]{ 1, 2, Complex(2,3) };
	std::cout << v[0] << v[1] << v[2] << v[3];

	std::cout << std::endl;

	Complex *pc = new Complex[4]{ 1, 2, Complex(2,3) };
	std::cout << pc[0] << pc[1].Re << std::endl << pc[2] << pc[3];

	delete[] pc;
}