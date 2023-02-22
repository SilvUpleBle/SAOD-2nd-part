#include <iostream>
using namespace std;

void rotate(int a[], int n, bool clockwise = false);
void rotate2(int a[], int n, bool clockwise = false);

int main()
{
	int a[5]{ 1,2,3,4,5 };
	for (int i = 0; i < 5; i++)
		cout << a[i] << ' ';
	cout << endl;

	for (int* p = a; p - a < 5; p++)
		cout << *p << "\t p = " << p << "\t a = " << a << "\t p - a = " << p - a << endl;
	cout << endl;

	rotate(a, 5, true);
	for (int i = 0; i < 5; i++)
		cout << a[i] << ' ';
	cout << endl;
}

void rotate(int a[], int n, bool clockwise)
{
	if (clockwise)
	{
		int x = a[n - 1];
		for (int i = n - 1; i > 0; i--)
			a[i] = a[i - 1];
		a[0] = x;
	}
	else
	{
		int x = a[0];
		for (int i = 1; i < n; i++)
			a[i - 1] = a[i];
		a[n - 1] = x;
	}
}

void rotate2(int a[], int n, bool clockwise)
{
	if (clockwise)
	{
		int x = a[n - 1];
		for (int* p = a + n - 1; p - a > 0; p--)
			*p = *(p - 1);
		*a = x;
	}
	else
	{
		int x = a[0];
		for (int* p = a + 1; p - a < n; p++)
			*(p - 1) = *p;
		*(a + n - 1) = x;
	}
}
