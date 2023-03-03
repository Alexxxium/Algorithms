#pragma once
#include <iostream>
#include <initializer_list>


template <class T>
struct Node
{
	T data;
	Node *prev, *next;

	Node(T vl): data(vl) { prev = next = nullptr; }
};


template <class T>
class LinkList
{
private:

	Node<T> *first, *last;
	int size;

	Node<T>* getNode(const int);

public:

	 LinkList(): size(0) { first = last = nullptr; }
	 ~LinkList();


	int lenght()				   { return size;	      }
	bool is_empty()				   { return first == nullptr; }
	T& operator[](const int index) { return getNode(index)->data; }


	void push_front(T);
	void push_back(T);
	void pop_front();
	void pop_back();

	void insert(const int, T);
	void pop_insert(const int);

	void outLinkList();
};


template<typename T>
Node<T>* LinkList<T>::getNode(const int index)
{
	if (is_empty() || index < 0 || index >= size)
		throw 1;


	if (index > size / 2)			
	{
		Node<T> *ptr = last;
		for (int i = 0; i < (size - 1 - index); ++i)
			ptr = ptr->prev;

		return ptr;
	}
	else							
	{
		Node<T> *ptr = first;
		for (int i = 0; i < index; ++i)
			ptr = ptr->next;

		return ptr;
	}

}
template<typename T>
LinkList<T>::~LinkList()
{
	Node<T> *ptr = first;
	Node<T> *buff;
	while (ptr)
	{
		buff = ptr;
		ptr = ptr->next;
		delete buff;
	}
}


template<typename T>
void LinkList<T>::push_front(T vl)
{
	Node<T> *newData = new Node<T>(vl);

	if (is_empty())
		first = last = newData;
	else
	{
		first->prev = newData;
		newData->next = first;
		first = newData;
	}
	++size;
}
template<typename T>
void LinkList<T>::push_back(T vl)
{
	Node<T> *newData = new Node<T>(vl);

	if (is_empty())
		first = last = newData;
	else
	{
		last->next = newData;
		newData->prev = last;
		last = newData;
	}
	++size;
}
template<typename T>
void LinkList<T>::pop_front()
{
	if (is_empty())
		return;

	Node<T> *buff = first->next;

	delete first;
	if (!buff)						
		first = last = nullptr;
	else
	{
		first = buff;
		first->prev = nullptr;
	}


	--size;
}
template<typename T>
void LinkList<T>::pop_back()
{
	if (is_empty())
		return;

	Node<T> *buff = last->prev;

	delete last;
	if (!buff)
		last = first = nullptr;
	else
	{
		last = buff;
		last->next = nullptr;
	}

	--size;
}
template<typename T>
void LinkList<T>::insert(const int index, T vl)
{
	Node<T> *indexNode = getNode(index);		

	if (index == 0)
	{
		push_front(vl);
		return;
	}

	Node<T> *newData = new Node<T>(vl);

	Node<T> *buff = indexNode->prev;

	buff->next = newData;
	newData->prev = buff;
	newData->next = indexNode;
	indexNode->prev = newData;

	++size;
}
template<typename T>
void LinkList<T>::pop_insert(const int index)
{
	Node<T> *del = getNode(index);

	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == size - 1)
	{
		pop_back();
		return;
	}

	del->prev->next = del->next;
	del->next->prev = del->prev;
	delete del;

	--size;
}

template<typename T>
void LinkList<T>::outLinkList()
{
	int it(0);
	std::cout << "\n";

	if (is_empty())
	{
		std::cout << "List is empty!\n\n";
		return;
	}
	Node<T> *ptr = first;
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
