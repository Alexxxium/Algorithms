#pragma once
#include <iostream>


template <class T>
struct Node
{
	Node *next;
	T data;
	Node(T vl): next(nullptr), data(vl) {}
};



template <class T>
class List
{
private:

	int lenght = 0;
	Node<T> *first, *last;


	Node<T>* getNode(const int);

public:

	  List(): lenght(0) { first = last = nullptr; }
	 ~List();
	

	void push_front(T);
	void push_back(T);
	void pop_front();
	void pop_back();


	int size()      { return lenght; }
	bool is_empty() { return first == nullptr; }

	T& operator[](const int index) { 
		return getNode(index)->data; 
	}


	void insert(const int, T);
	void pop_insert(const int);


	void outList();
};


template <typename T>
List<T>::~List()
{
	Node<T> *ptr = first, *del = first;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		delete del;
	}
}
template <typename T>
Node<T>* List<T>::getNode(const int index)
{
	if (is_empty() || index < 0 || index >= lenght)
		throw 1;

	Node<T> *ptr = first;
	for (int i = 0; i < index; ++i)
		ptr = ptr->next;

	return ptr;
}



template <typename T>
void List<T>::push_front(T vl)
{
	Node<T>* newData = new Node<T>(vl);

	if (is_empty())						// для первого элемента в списке
		first = last = newData;
	else
	{
		newData->next = first;
		first = newData;
	}
	++lenght;
}
template <typename T>
void List<T>::push_back(T vl)
{
	Node<T> *newData = new Node<T>(vl);

	if (is_empty())						// для первого элемента в списке
		first = last = newData;
	else
	{
		last->next = newData;
		last = newData;
	}
	++lenght;
}
template <typename T>
void List<T>::pop_front()
{
	if (is_empty())
		return;

	Node<T> *buff = first;
	first = first->next;
	delete buff;

	--lenght;
}
template <typename T>
void List<T>::pop_back()
{
	if (is_empty())
		return;

	Node<T> *buff = first, *ptr = first;

	if (lenght == 1)						
	{
		pop_front();
		return;
	}

	while (ptr->next)						// доходим до предспоследнего узла
	{
		buff = ptr;
		ptr = ptr->next;
	}
	delete ptr;								
	last = buff;
	last->next = nullptr;					// забываем последний узел 
	--lenght;
}
template <typename T>
void List<T>::insert(const int index, T vl)
{
	if (is_empty() || index >= lenght || index < 0)
		throw 1;

	if (lenght == 1 || index == 0)
	{
		push_front(vl);
		return;
	}

	Node<T> *newData = new Node<T>(vl);
	Node<T> *prev = first, *ptr = first;
	for (int i = 0; i < index; ++i)
	{
		prev = ptr;
		ptr = ptr->next;
	}

	prev->next = newData;
	newData->next = ptr;

	++lenght;
}
template <typename T>
void List<T>::pop_insert(const int index)
{
	if (is_empty() || index >= lenght || index < 0)
		throw 1;

	if (index == 0)
	{
		pop_front();
		return;
	}

	if (index == lenght - 1)
	{
		pop_back();
		return;
	}

	Node<T> *ptr = first, *prev = first;
	for (int i = 0; i < index; ++i)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	prev->next = ptr->next;
	delete ptr;
	--lenght;
}


template <typename T>
void List<T>::outList()
{
	Node<T> *ptr = first;
	int it(0);

	std::cout << "\n";
	if (is_empty())
	{
		std::cout << "\nlist is empty!\n\n";
		return;
	}

	while (ptr)
	{
		++it;
		std::cout << ptr->data << '\t';
		ptr = ptr->next;
		if (it % 10 == 0)
			std::cout << '\n';
	}
	std::cout << "\n\n" << std::endl;
}