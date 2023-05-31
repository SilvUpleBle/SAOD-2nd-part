// SufTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SuffixTree.h"
#include <string>

// Получает метку ребра
string GetLabel(STLink *pLnk)
{
	// Выясняем длину метки
	int lnkLen = pLnk->Length();
	// Сохраняем символ за меткой
	char ch = ((const char *)(*pLnk))[lnkLen];
	// Получаем указатель на начало метки
	char *p = (char*)(const char *)(*pLnk);
	// Ограничиваем ее 0
	p[lnkLen] = 0;
	// Строим строку
	string t = (const char *)(*pLnk);
	// Восстанавливаем символ, который заменяли 0
	p[lnkLen] = ch;

	return t;
}
//Пробегает по дереву и выводит его на консоль
void IterateTree(STNode *node, string pref = ". ")
{
	for (int i = 0; i < AlphaBetSize; i++)
	{
		STLink * pLnk = node->GetLink(i);
		if (pLnk != 0)
		{
			// Нашли внутренний узел (не лист)
			if (pLnk->GetTarget()->IsNode())
			{
				string t = GetLabel(pLnk);
				// Добавим в префикс метку ребра и стрелку
				t = pref + t + " -> ";
				// проходим поддерево 
				IterateTree(pLnk->GetNode(), t);
			}
			else // Нашли лист
			{
				// Добавим в префикс метку ребра и =
				string t = GetLabel(pLnk);
				t = pref + t + "\t = ";
				// Выводим префикс ребра и полный суффикс с позиции указанной в листе
				
				cout << '['; cout.width(2); cout<< (int)*(pLnk->GetTarget()) << ']' << t << '"' << SuffixTree::GetData() + (int)*(pLnk->GetTarget()) << '"' << endl;
			}
		}
	}
}

int main()
{
	char s[] = "sosiska_";
	s[strlen(s) - 1] = char(AlphaBetSize - 1);

	SuffixTree::Init(s);

	cout << SuffixTree::GetSize() << ' ' << SuffixTree::GetData() << endl<<endl;

	std::cout << SuffixTree::FindPattern("sis") << std::endl;
	std::cout << SuffixTree::Contains("sis");

	cout << endl;
    return 0;
}

