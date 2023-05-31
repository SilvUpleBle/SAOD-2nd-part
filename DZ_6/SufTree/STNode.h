#pragma once
#include "STLink.h"

#define AlphaBetSize 127



class SuffixTree;
// Класс внутренних узлов дерева	
class STNode
{
	friend class SuffixTree;
	// Массив ребер дерева размером AlphaBetSize;
	// Метка i-го ребра начинается с символа, с кодом i
	STLink **links;	
public:

	STNode() {
		links = new STLink* [AlphaBetSize] {0};
	}
	~STNode() {
		delete[]links;
	}

	// Вовзращает ребро из узла, метка которго начинается с кода i.
	STLink *GetLink(unsigned char i) { return links[i]; }
	void SetLink(STLink *pLnk) { links[(unsigned char)(*pLnk)] = pLnk; }
};

