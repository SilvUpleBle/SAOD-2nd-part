#pragma once
#include <string>
#include <algorithm>

class RWF
{
	int **pm;
	int M, N;
	std::string s, t;
public:
	RWF() {}

	RWF(const RWF&) = delete;

	~RWF()
	{
		for (int i = 0; i < M + 1; i++)
			delete[] pm[i];
		delete[] pm;
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
        
		for (int i = M; i >= 0; i--)
			pm[i][N] = M - i;
		for (int i = N; i >= 0; i--)
			pm[M][i] = N - i;
		for (int i = M - 1; i >= 0; i--)
		{
			for (int j = N - 1; j >= 0; j--)
			{
				pm[i][j] = min_from_three(pm[i + 1][j] + 1, pm[i][j + 1] + 1,
					pm[i + 1][j + 1] + (s[i] == t[j] ? 0 : 1));
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

private:
	int min_from_three(int a, int b, int c)
	{
		int m = std::min(a, b);
		m = std::min(m, c);
		return m;
	}
};
