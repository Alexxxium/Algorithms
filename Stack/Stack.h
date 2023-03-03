#pragma once
#include <iostream>


template<typename T>
struct Node
{
	T data;
	Node *next;

	Node(T vl): next(nullptr), data(vl) {}
};



template <class T>
class Stack
{
private:

	Node<T> *Top;
	int size;

public:

	 Stack(): Top(nullptr), size(0) {}
	 ~Stack();


	bool is_empty() { return Top == nullptr; }
	int lenght()	{ return size;           }

	T& top() { 
		if (is_empty()) throw 1;
		return Top->data; 
	}


	void push(T);
	void pop();

	
	void outStack();
};


template<typename T>
Stack<T>::~Stack()
{
	Node<T> *ptr = Top, *del;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		delete del;
	}
}

template<typename T>
void Stack<T>::push(T vl)
{
	Node<T> *newData = new Node<T>(vl);

	if (is_empty())
		Top = newData;
	else
	{
		newData->next = Top;
		Top = newData;
	}

	++size;
}
template<typename T>
void Stack<T>::pop()
{
	if (is_empty())
		return;

	Node<T>* buff = Top->next;
	delete Top;
	Top = buff;

	--size;
}
template<typename T>
void Stack<T>::outStack()
{
	Node<T> *ptr = Top;

	std::cout << '\n';
	if (is_empty())
	{
		std::cout << "Stack is empty!\n\n";
		return;
	}

	int it(0);
	std::cout << "Top ->:\t";

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