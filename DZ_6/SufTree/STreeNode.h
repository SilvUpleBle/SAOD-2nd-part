#pragma once

#include "STNode.h"
// Класс обощенного узла дерева
// Может быть как внутренним узлом STNode,
//  так и листом - целое

enum class STNodeTypes { SNodeType, IntType };

// Класс-объединение внутренних узлов дерва суффиксов (STNode) и листьев (int)
class STreeNode
{
public:
	STreeNode() :type(STNodeTypes::SNodeType), Node()
	{
	}

	STreeNode(int N) :type(STNodeTypes::IntType), StartPosition(N)
	{
	}
	~STreeNode() {
		if (type == STNodeTypes::SNodeType) Node.~STNode();
	}
	
	//Выясняет, является ли узел внутреннним (STNode). 
	//Если нет, то это лист. Его значение - начало соответствующего суффикса
	bool IsNode() { return type == STNodeTypes::SNodeType; }

	// Для листа получит его значение (индекса начала соответствующего суффикса)
	operator int() {
		if (type == STNodeTypes::IntType)
			return StartPosition;
		throw runtime_error("Node is not leave.");
	}
	
	STNodeTypes type;
	union {
		STNode Node;
		int StartPosition;
	};
};
