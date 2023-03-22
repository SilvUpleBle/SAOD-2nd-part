#include "PrefTree.h"
void PrefTree::insert(std::string text)
{
	bool isOnList;
	std::shared_ptr<Node> currentNode = root;
	for (char ch : text)
	{
		isOnList = false;
		if (isalpha(ch) || ch == '\'') //ch != ' ' && ch != '.' && ch != ',' && ch != '/' && ch != ':' && ch != ';' && ch != '&' && ch != '$' && ch != '#' && ch != '@' && ch != '[' && ch != ']' && ch != '{' && ch != '}' && ch != '!' && ch != '?' && ch != '\\' && ch != '(' && ch != ')' && ch != '\"' && ch != '-' && ch != '*' && ch != '\t' && ch != '\n'
		{
			for (std::shared_ptr<Node> curr : currentNode->next)
			{
				if (curr->ch == ch)
				{
					currentNode = curr;
					isOnList = true;
					break;
				}
				else
					isOnList = false;
			}

			if (!isOnList)
			{
				currentNode->next.push_back(std::make_shared<Node>(Node(ch)));
				currentNode = currentNode->next.back();
			}
		}
		else
		{
			currentNode->count++;
			if (currentNode->count == 1)
				size++;
			currentNode = root;
		}
	}
}

bool PrefTree::find(std::string word)
{
	std::shared_ptr<Node> currentNode = root;
	for (char ch : word)
	{
		for (std::shared_ptr<Node> curr : currentNode->next)
		{
			if (ch == curr->ch)
			{
				currentNode = curr;
				std::cout << curr->ch << std::endl;
			}
			else
				return false;
		}
	}
	if (currentNode->count > 0)
		return true;
	else
		return false;
}

size_t PrefTree::get_size() { return size; }

size_t PrefTree::get_count(std::string word)
{
	std::shared_ptr<Node> currentNode = root;
	for (char ch : word)
	{
		for (std::shared_ptr<Node> curr : currentNode->next)
		{
			if (ch == curr->ch)
				currentNode = curr;
		}
	}
	return currentNode->count;
}