#pragma once
#include <iostream>
template <typename T>

class LList
{
private:
	struct Node		//служебная структура для создания узлов листа, хранящая значение узла и ссылку на следующий узел
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
	Node* getNode(size_t index) const //возвращает узел по ссылке 
	{
		Node* ptr = root;
		for (size_t i = 0; i < index; i++)
			ptr = ptr->next;
		return ptr;
	}

public:
	LList() { root = nullptr;  Node* sentinel = new Node(); this->sentinel = sentinel; }	//создаём служебный узел (далее sentinel) при создании объекта класса
	~LList() { clear(); delete sentinel; sentinel = nullptr; };

	void push_back(T value) //создание нового элемента после остальных
	{
		Node* sentinel = new Node();		//создание служебный узел
		if (size == 0)					//при создании первого элемента (меняем значения уже существующего sentinel)
		{								//sentinel присваиваем созданный узел и помещаем его позади изменённого узла
			this->sentinel->value = value;
			root = this->sentinel;
			this->sentinel = sentinel;
			root->next = sentinel;
		}
		else							//при созданиие НЕ первого элемента (меняем значения уже существующего sentinel)
		{								//sentinel присваиваем новый созданный узел и помещаем его позади изменённого узла
			this->sentinel->value = value;
			this->sentinel->next = sentinel;
			this->sentinel = sentinel;
		}
		size++;
	}

	void push_front(T value) //создание нового элемента перед остальными
	{
		if (size == 0)					//при создании первого элемента (меняем значения уже существующего sentinel и создаём новый служебный узел)
		{								//sentinel присваиваем новый созданный узел и помещаем его позади изменённого узла
			this->sentinel->value = value;
			root = this->sentinel;
			Node* sentinel = new Node();
			this->sentinel = sentinel;
			root->next = sentinel;
		}
		else							//при создании НЕ первого элемента (создаём дополнительный узел с нужным значением
		{								//позади него ставим нынешний root и переприсваиваем root на новый узел)
			Node* tmp = new Node(value);
			tmp->next = root;
			root = tmp;
		}
		size++;
	}

	void insert(size_t index, T value) //поместить новый элемент по индексу
	{
		if (index + 1 > size) //если index вне зоны листа, то выбросить ошибку
		{
			throw std::range_error("Index out of range!");
		}
		else
		{
			if (index == 0) //если index нулевой, то используем push_front
				push_front(value);
			else			//ecли index НЕнулевой, то создаём новый узел с данными заменяемого узла, у заменяемого узла меняем значение и ставим позади него новый созданный узел
			{
				Node* ptr = getNode(index);
				Node* tmp = new Node(ptr->value, ptr->next);
				ptr->value = value;
				ptr->next = tmp;
			}
			size++;
		}
	}

	void pop_back() //удаляет последний элемент листа
	{
		if (size > 0)	//проверка на пустой лист
		{
			if (size == 1)	//если в листе только 1 элемент, то удаляем узел, хранящийся по ссылке в root
			{
				delete root;
				root = nullptr;
			}
			else			//если в листе ещё есть элементы, то получаем ссылку на предпоследний элемент, с помощью него удаляем последний узел
			{				//и переприсваиваем предпоследнему элементу следующий на служебный узел
				Node* tmp = getNode(size - 2);
				delete tmp->next;
				tmp->next = this->sentinel;
			}
			size--;
		}
		else
			throw std::range_error("There`s nothing in list!");
	}

	void pop_front() //удаляет первый жэлемент листа 
	{
		if (size > 0)	//проверка на пустой лист
		{
			if (size == 1)	//если в листе только 1 элемент, то удаляем узел, хранящийся по ссылке в root
			{
				delete root;
				root = nullptr;
			}
			else			//если в листе ещё есть элементы, то создаём буферную перменную для хранения нового корня (следующего после root)
			{				//удаляем узел по ссылке из root и присваиваем root новый узел
				Node* new_root = root->next;
				delete root;
				root = new_root;
			}
			size--;
		}
		else
			throw std::range_error("There`s nothing in list!");
	}

	void remove_at(size_t index) //удаление элемента по индексу
	{
		if (index + 1 > size)	//если index вне зоны листа, то выбросить ошибку
		{
			throw std::range_error("Index out of range!");
		}
		else
		{
			if (index == 0)		//если index = 0 или последнему элементу, то вызываем pop_front и pop_back соответствующе
				pop_front();
			if (index == size - 1)
				pop_back();

			Node* tmp = getNode(index - 1);		//если не index не 0 и не последний, то находим узел перед удаляемым, ставим позади него узел, который идёт
			Node* next_node = tmp->next->next;	//после удаляемого и удаляем узел по индексу
			delete tmp->next;
			tmp->next = next_node;
			size--;
		}
	}

	T& operator[] (const size_t index) //записть элмента по индексу
	{
		if (index + 1 > size)	//проверка на выход индекса за массив
			throw std::range_error("Index out of range!");
		else
			return getNode(index)->value;
	}

	T const& operator[] (const size_t index) const //чтение элемента по индексу
	{
		if (index + 1 > size)	//проверка на выход индекса за массив
			throw std::range_error("Index out of range!");
		else
			return getNode(index).value;
	}

	size_t get_size() const { return size; } //возвращает размера листа
	
	bool empty() const { if (size == 0) return true; else return false; } //проверка листа на пустоту

	void clear() //удаление элементов листа
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

	T front() const { return root->value; } //возвращает знечение первого узла

	T back() const { return getNode(size - 1)->value; } //возвращает значение последнего листа
};