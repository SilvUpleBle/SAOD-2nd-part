#pragma once
#include "STreeNode.h"


// ����� ����������� ������� ��� �������� ������ � ���������� ������ ���������
class SuffixTree
{
	static const char *pszData;	// ��������� �� ����� � ������� ����� �����
	static int N;				// ����� ����� ������
	static STNode *root;		// �������� ������� ������
public:
	// ��������� ����������� �� ���������, �������� ����������� � ������������.
	SuffixTree() = delete;
	SuffixTree(SuffixTree const&) = delete;
	SuffixTree& operator=(SuffixTree const&) = delete;

	// ��������� ���� � ������ ������ ���������
	static void Init(const char*s)
	{
		N = strlen(s);
		pszData = s;
		root = new STNode();
		
		// ��������� ��� �������� � ������
		for (int i = 0; i < N; i++)
			addSuffix(i);
	}
	static STNode* GetRoot()
	{
		return root;
	}
	// ���������� ������ ������, ��� �������� ��������� ������
	static int GetSize()
	{
		return N;
	}
	// ���������� ��������� �� �����, ��� �������� ��������� ������
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
	// ��������� �������, ������� ���������� � ������� n � ������ pszData.
	static void addSuffix(int n)
	{
		if (n < 0 || n >= N)
			throw out_of_range("index out of range");
		
		// ������ ����� ������� ����� ���� ���� - ����� ������ ������� ������ ��������;
		// ������� ����� � ������ ������� ��������.
		STLink *pLnk = new STLink(pszData + n, N - n);
		pLnk->SetTarget(new STreeNode(n));

		STNode *node = root;
		while (1)
		{
			// ����� ����, � ������� ��� ��������������� �����
			if (node->GetLink(pszData[n]) == 0)
			{
				node->SetLink(pLnk);
				break;
			}
			else // ����������� �����
			{
				STLink *pLnkCurrent = node->GetLink(pszData[n]);
				int k = pLnkCurrent->PrefixLen(*pLnk);
				// ����� ��������� �������� ��������� ��������
				// �������� �������� ���� �� �����, �.�. ������� ������������� ���������� �������� (\xFF).
				if (k == pLnkCurrent->Length())
				{
					// ��������� ��������� ����� ��������, ������� ������� � ������� �����:
					// 1. �������� ����� �������� �����
					pLnk->LTruncate(k);
					// 2. �������� ������ �������� �� ����� ����������
					n += k;
					// ����� �������� ���� ����� � �������� ��������.
					node = pLnkCurrent->GetNode();
				}
				// ���� ������ ��������� ���������� ������� � �����.
				// ����� ������� ����� ���� � �������� ��� � ������� ����� � ������� k
				else
				{
					// ������� ����� ����
					STreeNode * pnewNode = new STreeNode();
					
					//� ����� ����� (� ���� ����� �� ����� �����, ������� ����� � �������� ����)
					STLink *pLnkTail = new STLink(*pLnkCurrent);
					// ��������� ���� ����� �����
					pLnkTail->LTruncate(k);
					// ... � ������ ������
					pLnkCurrent->RTruncate(k);
					// �������� ����� �������� �����
					pLnk->LTruncate(k);
					// �������� ������ �������� �� ����� ����������
					n += k;
					// �������� � ������ ����� ����
					pLnkCurrent->SetTarget(pnewNode);
					// � ������ ����� �������� ������� �����
					pnewNode->Node.SetLink(pLnkTail);
					// ���������� � ���� ������� ������������ ��������
					pnewNode->Node.SetLink(pLnk);
					break;
				}
			}
		}
	}
};

