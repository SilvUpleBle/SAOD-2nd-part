#pragma once
#include <iostream>
#include <string>
#include <list>

class PrefTree
{
private:
	struct Node
	{
		Node() { this->ch = ' '; };
		Node(char ch) { this->ch = ch; };
		~Node() {};
		char ch;
		int count = 0;
		std::list<std::shared_ptr<Node>> next;
	};
	size_t size = 0;
	std::shared_ptr<Node> root = std::make_shared<Node>(Node());
public:
	PrefTree() {};

	~PrefTree() {};

	void insert(std::string text);

	bool find(std::string word);

	size_t get_size();

	size_t get_count(std::string word);
};