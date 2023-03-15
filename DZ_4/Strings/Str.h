#pragma once
class Str
{
private:
	char* m_pszText;

public:

	Str() { m_pszText = new char[1] {0}; }
	
	Str(const char* p)
	{
		
		if (p) 
		{
			m_pszText = new char[strlen(p) + 1];
			strcpy_s(m_pszText, strlen(p) + 1, p);
		}
		else
			m_pszText = new char[1] {0};
	}
	
	Str(const Str& s)
	{
		m_pszText = new char[strlen(s.m_pszText) + 1];
		strcpy_s(m_pszText, strlen(s.m_pszText) + 1, s.m_pszText);
	}

	~Str() { delete[] m_pszText; }
	
	const Str& operator= (const Str& s)
	{
		if (&s == this) 
			return *this;

		delete[] m_pszText;
		m_pszText = new char[strlen(s.m_pszText) + 1];
		strcpy_s(m_pszText, strlen(s.m_pszText) + 1, s.m_pszText);
		return *this;
	}

	operator const char* () { return m_pszText; }

	Str& operator+=(const char* sz)
	{
		size_t new_length = strlen(m_pszText) + strlen(sz) + 1;
		size_t old_length = strlen(m_pszText);
		char* temp = new char[new_length];

		for (size_t i = 0; i < old_length; i++)
		{
			temp[i] = m_pszText[i];		//old_length всегда <= new_length, не понимаю, почему он предупреждение кидает
		}
		for (size_t j = old_length; j < new_length; j++)
		{
			temp[j] = sz[j - old_length];
		}

		delete[] m_pszText;
		m_pszText = new char[new_length];
		for (size_t i = 0; i < new_length; i++)
		{
			m_pszText[i] = temp[i];
		}

		delete[] temp;
		return *this;
	}

	Str operator+(const char* sz)
	{
		size_t new_length = strlen(m_pszText) + strlen(sz) + 1;
		Str out;

		out.m_pszText = new char[new_length] {0};
		out += m_pszText;
		out += sz;
		return out;
	}
};