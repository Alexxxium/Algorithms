#pragma once
#pragma warning(disable: 6386)

#include <iostream>

namespace algs
{
	template <class T>
	class Heap
	{
	private:

		T *arr;

		const float redist = 2;
		const size_t default_capacity = 32;

		size_t lenght, capacity;

	public:

		explicit Heap(const int sz = 0);

		Heap(Heap<T>&&) noexcept;
		Heap(const Heap<T>&) noexcept;
		void operator = (Heap<T>&&) noexcept;
		void operator = (const Heap<T>&) noexcept;

		~Heap() noexcept { delete[] arr; }


	private:

		inline void swap(const size_t, const size_t);

		void balance(const size_t) noexcept;
		void redist_memory() noexcept;


	public:

		bool isEmpty() const noexcept { return lenght == 0; }
		size_t size()  const noexcept { return lenght; }

		void insert(const T&);
		const T& remove();

		void outHeap() const noexcept;
		void outArray() const noexcept;

		T* getSortArray() const noexcept;
	};
}

#include "Heap.inl"


