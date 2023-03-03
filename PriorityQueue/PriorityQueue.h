#pragma once

#include "../Heap/Heap.h"

template <class T>
class PriorityQueue
{
private:
	Heap<T> heap;

public:
	~PriorityQueue() = default;
	PriorityQueue(const int size = 0) try: heap(size){}
	catch (...)
	{
		std::cerr << "\nError:\tInvalide lenght!\n";
	}

	bool isEmpty()			{ return heap.isEmpty();	}
	size_t size()			{ return heap.size();		}
	T pop()				{ return heap.pop();		}
	void push(const T vl)   	{	 heap.push(vl);		}
	T* getArray()			{ return heap.getSortArray();	}

	void out()
	{
		T *ptr = new T[heap.size()];
		ptr = heap.getSortArray();
		for (int i = 0; i < heap.size(); ++i)
			std::cout << ptr[i] << ' ';
		std::cout << std::endl;
		delete[] ptr;
	}
};
