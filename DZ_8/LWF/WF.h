#pragma once
#include <string>
#include <algorithm>

class WF
{
	int **pm;
	int M, N;
	std::string s, t;
public:
	WF()
	{

	}
	void Init(const char *sc, const char *tc)
	{
		s = std::string(sc);
		t = std::string(tc);
		M = s.size();
		N = t.size();
		pm = new int*[M + 1];
		for (int i = 0; i <= M; i++)
			pm[i] = new int[N + 1];
		
		for (int i = 0; i <= M; i++)
			pm[i][0] = i;
		for (int i = 0; i <= N; i++)
			pm[0][i] = i;
		for (int i = 1; i <= M; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				pm[i][j] = min_from_three(pm[i - 1][j] + 1, pm[i][j - 1] + 1,
					pm[i - 1][j - 1] + (s[i - 1] == t[j - 1] ? 0 : 1));
			}
		}
	}
	int Rows()
	{
		return M;
	}
	int Columns()
	{
		return N;
	}
	int Get(int i, int j)
	{
		if (i > M || j > N)
			throw "out_of_range";
		return pm[i][j];
	}
	void Set(int i, int j, int val)
	{
		if (i > M || j > N)
			throw "out_of_range";
		pm[i][j] = val;
	}
	~WF()
	{
		for (int i = 0; i < M + 1; i++)
			delete pm[i];
		delete[] pm;
	}
	WF(const WF&) = delete;
private:
	int min_from_three(int a, int b, int c)
	{
		int m = std::min(a,b);
		m = std::min(m, c);
		return m;
	}
};