#pragma once
#include "_str.h"
#include <string.h>

class Str {
	_str* m_pStr;
public:
	Str() { m_pStr = new _str; }		// если не копия, то создаем
	Str(const char* p) {				// новый ресурс
		m_pStr = new _str(p);
	}
	~Str() {
		m_pStr->Release(); 		// Не уничтожаем ресурс!
	}							// Уменьшаем счетчик ссылок!

	int len() const {
		return strlen(m_pStr->m_pszData);
	}

	int rfind(const char *t, int off) const { //найденное совпадение не может начинаться после off (если вхождений нет, то -1)
		int index = -1;
		int length = strlen(t);
		bool flag = false;
		for (int i = 0; i < off; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (m_pStr[0].m_pszData[j + i] == t[j]) 
				{
					if (j == length - 1)
						flag = true;
					continue;
				}
				else {
					break;
				}
			}
			if (flag) {
				flag = false;
				index = i;
			}
		}
		return index;
	}
};