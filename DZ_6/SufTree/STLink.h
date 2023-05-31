#pragma once
#include <assert.h>
#include "STreeNode.h"

class STreeNode;
class STNode;

// Класс метки для ребра дерева суфиксов
class Label
{
public:
	// Положение начала метки в тексте
	const char *pos;
	// Длина метки
	int len;
	Label(const char *p, int len) :pos(p), len(len) {}
};
// Класс ребер для дерева суффиксов
class STLink
{
	Label lbl;
	STreeNode *pTarget;
public:

	STLink(const char *p, int len) :lbl(p, len)
	{
	}
	~STLink() {}

	operator const char *() const { return lbl.pos; }
	operator const char () const { return *lbl.pos; }
	
	// Присваивает конечный узел ребра
	void SetTarget(STreeNode *p) {
		pTarget = p;
	}
	// Получает конечный узел ребра
	STreeNode *GetTarget() {
		return pTarget;
	}
	// Возвращает длину метки ребра
	int Length() { return lbl.len; }

	// Получает указатель на конечный узел ребра, если не лист
	// Для листа вбрасывает исключение
	STNode *GetNode() const;

	// Вычисляет длину префикса строки s, совпадающего с префиксом метки
	int PrefixLen(const char * s) const
	{
		for (int i = 0; i < lbl.len; i++)
			if (s[i] != lbl.pos[i])
				return i;
		return lbl.len;
	}

	// Обрезает метку ребра на n символов слева.
	// Переносит начало и уменьшает длину
	void LTruncate(int n)
	{
		assert(n < lbl.len);
		lbl.pos += n;
		lbl.len -= n;
	}
	// Обрезает метку ребра на n символов справа.
	// Сохраняет начало, но уменьшает длину
	void RTruncate(int n)
	{
		lbl.len = n;
	}
};

