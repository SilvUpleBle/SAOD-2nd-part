#include "utils2.h"

void utils2::copy(char a[], char b[])
{
	for (char* pd = b, *ps = a; *pd++ = *ps++;);
}

void utils2::copy2(char a[], char b[])
{
	for (int i = 0; i < strlen(a); i++)
		b[i] = a[i];
}

int utils2::len(const char* s)
{
	int counter = 0;

	while (*(s + counter) != '\0')
	{
		counter++;
	}

	return counter;
}

int utils2::compare(const char* s, const char* t)
{
	int lenS = len(s);
	int lenT = len(t);
	if (lenS > lenT)
		return 1;
	else
		if (lenS < lenT)
			return -1;
		else
			return 0;
}