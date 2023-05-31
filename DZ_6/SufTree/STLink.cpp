#include "stdafx.h"
#include "STreeNode.h"
#include "STLink.h"


STNode * STLink::GetNode() const {
	if (pTarget && pTarget->type == STNodeTypes::SNodeType)
		return &pTarget->Node;
	return NULL;
}
