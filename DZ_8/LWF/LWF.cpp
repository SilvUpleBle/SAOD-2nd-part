#include <iostream>
#include <limits>
#include "WF.h"
#include "RWF.h"

int Distance(WF& wf, RWF& rwf)
{
	if (wf.Rows() != rwf.Rows())
		throw "logic_error";
	int sum = std::numeric_limits<int>::max();
	for (int i = 0; i <= wf.Rows(); i++)
	{
		int nsum = wf.Get(i, wf.Columns()) + rwf.Get(i, 0);
		if (nsum < sum)
			sum = nsum;
	}
	return sum;
}

char* concat_chars(const char* v, const char* u)
{
	rsize_t sv = strlen(v), su = strlen(u);
	char* concat = new char[sv + su + 1];
	for (rsize_t i = 0; i < sv + su; i++)
	{
		if (i < sv) concat[i] = v[i];
		else concat[i] = u[i - sv];
	}
	concat[sv + su] = '\0';
	return concat;
}

void CompareDist(const char* s, const char* v, const char* u)
{
	char* t = concat_chars(v, u);
	WF svwf;
	RWF surwf;
	svwf.Init(s, v);
	surwf.Init(s, u);
	int dist = Distance(svwf, surwf);
	WF stwf;
	stwf.Init(s, t);
	std::cout << "Parallel: " << dist << ", Direct: " << stwf.Get(stwf.Rows(), stwf.Columns()) << std::endl;
	delete[] t;
}

int main()
{
	WF wf;
	wf.Init("no", "ono");
	for (int i = 0; i <= wf.Rows(); i++)
	{
		for (int j = 0; j <= wf.Columns(); j++)
			std::cout << wf.Get(i, j) << ' ';
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
	RWF rwf;
	rwf.Init("no", "ono");
	for (int i = 0; i <= rwf.Rows(); i++)
	{
		for (int j = 0; j <= rwf.Columns(); j++)
			std::cout << rwf.Get(i, j) << ' ';
		std::cout << std::endl;
	}

	return 0;
}