#pragma once
#include "STreeNode.h"


// Класс статических методов для хранения данных и построения дерева суффиксов
class SuffixTree
{
	static const char *pszData;	// Указатель на текст в котором будет поиск
	static int N;				// Общая длина текста
	static STNode *root;		// Корневой элемент дерева
public:
	// Запрещаем конструктор по умолчению, оператор копирования и присваивания.
	SuffixTree() = delete;
	SuffixTree(SuffixTree const&) = delete;
	SuffixTree& operator=(SuffixTree const&) = delete;

	// Заполняет поля и строит дерево суффиксов
	static void Init(const char*s)
	{
		N = strlen(s);
		pszData = s;
		root = new STNode();
		
		// Добавляем все суффиксы в дерево
		for (int i = 0; i < N; i++)
			addSuffix(i);
	}
	static STNode* GetRoot()
	{
		return root;
	}
	// Возвращает размер текста, для которого построено дерево
	static int GetSize()
	{
		return N;
	}
	// Возвращает указатель на текст, для которого построено дерево
	static const char* GetData()
	{
		return pszData;
	}

	static bool Contains(const char* s)
	{
		if (FindPattern(s) != -1) return true;
		else return false;
	}

	static int FindPattern(const char* t) {
		int index = 0;
		int length = strlen((char*)t);
		STNode* pNode = GetRoot();
		STLink* pLnk = pNode->GetLink((int)t[index]);

		while (index < length) {
			pLnk = pNode->GetLink((int)t[index]);
			if (pLnk == 0) return -1;

			int lnkLen = pLnk->Length();
			char ch = ((const char*)(*pLnk))[lnkLen];
			char* p = (char*)(const char*)(*pLnk);
			p[lnkLen] = 0;
			string tmp = (const char*)(*pLnk);
			p[lnkLen] = ch;

			for (char ch : tmp)
			{
				if (ch == t[index]) index++;
				else return -1;

				if (index == length) break;
			}
			pNode = pLnk->GetNode();
		}
		int begin = 999999999;
		int enter;
		while (pLnk->GetTarget()->IsNode()) {
			for (int i = 0; i < AlphaBetSize; i++)
			{
				pLnk = pNode->GetLink(i);
				if (pLnk != 0)
				{
					if (!pLnk->GetTarget()->IsNode()) {
						if ((int)*(pLnk->GetTarget()) < begin) {
							enter = (int)*(pLnk->GetTarget());
							if (enter == 0) break;
							begin = enter;
						}
					}
				}
			}
		}
		enter = (int)*(pLnk->GetTarget());
		return enter;
	}



private:
	// Добавляет суффикс, который начинается с индекса n в строке pszData.
	static void addSuffix(int n)
	{
		if (n < 0 || n >= N)
			throw out_of_range("index out of range");
		
		// Каждый новый суффикс имеет свой лист - целое равное индексу начала суффикса;
		// Создаем ребро с листом нужного значения.
		STLink *pLnk = new STLink(pszData + n, N - n);
		pLnk->SetTarget(new STreeNode(n));

		STNode *node = root;
		while (1)
		{
			// Нашли узел, в котором нет соответствующей ветви
			if (node->GetLink(pszData[n]) == 0)
			{
				node->SetLink(pLnk);
				break;
			}
			else // Анализируем ветвь
			{
				STLink *pLnkCurrent = node->GetLink(pszData[n]);
				int k = pLnkCurrent->PrefixLen(*pLnk);
				// Метка полностью является префиксом суффикса
				// Обратной ситуации быть не может, т.к. суффикс заканчивается уникальным символом (\xFF).
				if (k == pLnkCurrent->Length())
				{
					// Исключаем начальную часть суффикса, которая совпала с метокой ребра:
					// 1. Обрезали метку суффикса слева
					pLnk->LTruncate(k);
					// 2. Сместили начало суффикса на длину совпадения
					n += k;
					// Берем конечный узел ребра в качестве текущего.
					node = pLnkCurrent->GetNode();
				}
				// Есть только частичное совпадение суфикса и метки.
				// Нужно создать новый узел и вставить его в текущую метку в позицию k
				else
				{
					// Создали новый узел
					STreeNode * pnewNode = new STreeNode();
					
					//и копию ребра (у него такая же длина метки, позиция метки и конечный узел)
					STLink *pLnkTail = new STLink(*pLnkCurrent);
					// Укоротили одну метку слева
					pLnkTail->LTruncate(k);
					// ... а вторую справа
					pLnkCurrent->RTruncate(k);
					// Обрезали метку суффикса слева
					pLnk->LTruncate(k);
					// Сместили начало суффикса на длину совпадения
					n += k;
					// Вставили в разрыв новый узел
					pLnkCurrent->SetTarget(pnewNode);
					// В нужное место добавили остаток ребра
					pnewNode->Node.SetLink(pLnkTail);
					// Прикрепили к нему остаток вставляемого суффикса
					pnewNode->Node.SetLink(pLnk);
					break;
				}
			}
		}
	}
};

