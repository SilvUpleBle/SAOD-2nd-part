#pragma once
#include <iostream>
template <typename T>

class LList
{
private:
	struct Node		//��������� ��������� ��� �������� ����� �����, �������� �������� ���� � ������ �� ��������� ����
	{
		T value;
		Node* next = nullptr;
		Node() { this->value = 0; }
		Node(T value) { this->value = value; }
		Node(T value, Node* next) { this->value = value; this->next = next; }
		~Node() { value = 0; next = nullptr; }
	};
	size_t size = 0;
	Node *root, *sentinel;
	Node* getNode(size_t index) const //���������� ���� �� ������ 
	{
		Node* ptr = root;
		for (size_t i = 0; i < index; i++)
			ptr = ptr->next;
		return ptr;
	}

public:
	LList() { root = nullptr;  Node* sentinel = new Node(); this->sentinel = sentinel; }	//������ ��������� ���� (����� sentinel) ��� �������� ������� ������
	~LList() { clear(); delete sentinel; sentinel = nullptr; };

	void push_back(T value) //�������� ������ �������� ����� ���������
	{
		Node* sentinel = new Node();		//�������� ��������� ����
		if (size == 0)					//��� �������� ������� �������� (������ �������� ��� ������������� sentinel)
		{								//sentinel ����������� ��������� ���� � �������� ��� ������ ���������� ����
			this->sentinel->value = value;
			root = this->sentinel;
			this->sentinel = sentinel;
			root->next = sentinel;
		}
		else							//��� ��������� �� ������� �������� (������ �������� ��� ������������� sentinel)
		{								//sentinel ����������� ����� ��������� ���� � �������� ��� ������ ���������� ����
			this->sentinel->value = value;
			this->sentinel->next = sentinel;
			this->sentinel = sentinel;
		}
		size++;
	}

	void push_front(T value) //�������� ������ �������� ����� ����������
	{
		if (size == 0)					//��� �������� ������� �������� (������ �������� ��� ������������� sentinel � ������ ����� ��������� ����)
		{								//sentinel ����������� ����� ��������� ���� � �������� ��� ������ ���������� ����
			this->sentinel->value = value;
			root = this->sentinel;
			Node* sentinel = new Node();
			this->sentinel = sentinel;
			root->next = sentinel;
		}
		else							//��� �������� �� ������� �������� (������ �������������� ���� � ������ ���������
		{								//������ ���� ������ �������� root � ��������������� root �� ����� ����)
			Node* tmp = new Node(value);
			tmp->next = root;
			root = tmp;
		}
		size++;
	}

	void insert(size_t index, T value) //��������� ����� ������� �� �������
	{
		if (index + 1 > size) //���� index ��� ���� �����, �� ��������� ������
		{
			throw std::range_error("Index out of range!");
		}
		else
		{
			if (index == 0) //���� index �������, �� ���������� push_front
				push_front(value);
			else			//ec�� index ���������, �� ������ ����� ���� � ������� ����������� ����, � ����������� ���� ������ �������� � ������ ������ ���� ����� ��������� ����
			{
				Node* ptr = getNode(index);
				Node* tmp = new Node(ptr->value, ptr->next);
				ptr->value = value;
				ptr->next = tmp;
			}
			size++;
		}
	}

	void pop_back() //������� ��������� ������� �����
	{
		if (size > 0)	//�������� �� ������ ����
		{
			if (size == 1)	//���� � ����� ������ 1 �������, �� ������� ����, ���������� �� ������ � root
			{
				delete root;
				root = nullptr;
			}
			else			//���� � ����� ��� ���� ��������, �� �������� ������ �� ������������� �������, � ������� ���� ������� ��������� ����
			{				//� ��������������� �������������� �������� ��������� �� ��������� ����
				Node* tmp = getNode(size - 2);
				delete tmp->next;
				tmp->next = this->sentinel;
			}
			size--;
		}
		else
			throw std::range_error("There`s nothing in list!");
	}

	void pop_front() //������� ������ �������� ����� 
	{
		if (size > 0)	//�������� �� ������ ����
		{
			if (size == 1)	//���� � ����� ������ 1 �������, �� ������� ����, ���������� �� ������ � root
			{
				delete root;
				root = nullptr;
			}
			else			//���� � ����� ��� ���� ��������, �� ������ �������� ��������� ��� �������� ������ ����� (���������� ����� root)
			{				//������� ���� �� ������ �� root � ����������� root ����� ����
				Node* new_root = root->next;
				delete root;
				root = new_root;
			}
			size--;
		}
		else
			throw std::range_error("There`s nothing in list!");
	}

	void remove_at(size_t index) //�������� �������� �� �������
	{
		if (index + 1 > size)	//���� index ��� ���� �����, �� ��������� ������
		{
			throw std::range_error("Index out of range!");
		}
		else
		{
			if (index == 0)		//���� index = 0 ��� ���������� ��������, �� �������� pop_front � pop_back ��������������
				pop_front();
			if (index == size - 1)
				pop_back();

			Node* tmp = getNode(index - 1);		//���� �� index �� 0 � �� ���������, �� ������� ���� ����� ���������, ������ ������ ���� ����, ������� ���
			Node* next_node = tmp->next->next;	//����� ���������� � ������� ���� �� �������
			delete tmp->next;
			tmp->next = next_node;
			size--;
		}
	}

	T& operator[] (const size_t index) //������� ������� �� �������
	{
		if (index + 1 > size)	//�������� �� ����� ������� �� ������
			throw std::range_error("Index out of range!");
		else
			return getNode(index)->value;
	}

	T const& operator[] (const size_t index) const //������ �������� �� �������
	{
		if (index + 1 > size)	//�������� �� ����� ������� �� ������
			throw std::range_error("Index out of range!");
		else
			return getNode(index).value;
	}

	size_t get_size() const { return size; } //���������� ������� �����
	
	bool empty() const { if (size == 0) return true; else return false; } //�������� ����� �� �������

	void clear() //�������� ��������� �����
	{
		Node* tmp;
		for (int i = 0; i < size; i++)
		{
			tmp = root->next;
			delete root;
			root = tmp;
		}
		size = 0;
		root = nullptr;
	}

	T front() const { return root->value; } //���������� �������� ������� ����

	T back() const { return getNode(size - 1)->value; } //���������� �������� ���������� �����
};