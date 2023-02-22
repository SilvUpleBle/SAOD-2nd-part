#include "utils.h"

void utils::Swap(int& a, int& b)
{
	int c = b;

	b = a;
	a = c;
}