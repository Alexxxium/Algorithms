
namespace algs
{
	template<typename T>
	Heap<T>::Heap(const int sz): lenght(0)
	{
		if (sz < 0) throw 1;

		if (sz)
			capacity = sz;
		else
			capacity = default_capacity;

		arr = new T[capacity];
	}
	
	template<typename T>
	Heap<T>::Heap(const Heap<T> &heap) noexcept:
		capacity(heap.capacity),
		lenght(heap.lenght)
	{
		delete[] arr;

		arr = new T[capacity];

		for (int i = 0; i < lenght; ++i)
			arr[i] = heap.arr[i];
	}
	
	template<typename T>
	Heap<T>::Heap(Heap<T> &&heap) noexcept:
		capacity(heap.capacity),
		lenght(heap.lenght)
	{
		delete[] arr;
		arr = heap.arr;

		heap.arr = nullptr;
		heap.capacity = 0;
		heap.lenght = 0;
	}



	template<typename T>
	void Heap<T>::operator = (Heap<T> &&heap) noexcept
	{
		if (this == &heap) return;

		capacity = heap.capacity;
		lenght = heap.lenght;
		arr = heap.arr;

		heap.arr = nullptr;
		heap.capacity = 0;
		heap.lenght = 0;

	}
	
	template<typename T>
	void Heap<T>::operator = (const Heap<T> &heap) noexcept
	{
		if (&heap == this) return;

		lenght = heap.lenght;
		capacity = heap.capacity;

		delete[] arr;
		arr = new T[capacity];

		for (int i = 0; i < lenght; ++i)
			arr[i] = heap.arr[i];
	}



	template<typename T>
	void Heap<T>::redist_memory() noexcept
	{
		capacity *= redist;
		T *copy = arr;
		arr = new T[capacity];

		for (int i = 0; i < lenght; ++i)
			arr[i] = copy[i];			// <- C6386 и бла бла бла
		delete[] copy;
	}
	
	template<typename T>
	void Heap<T>::swap(const size_t indx1, const size_t indx2)
	{
		T buff = arr[indx1];
		arr[indx1] = arr[indx2];
		arr[indx2] = buff;
	}
	
	template<typename T>
	void Heap<T>::balance(const size_t indx) noexcept
	{
		int left = 2 * indx + 1;
		int right = 2 * indx + 2;

		if (left < lenght)
			if (arr[indx] < arr[left])
			{
				swap(indx, left);
				balance(left);
			}
		if (right < lenght)
			if (arr[indx] < arr[right])
			{
				swap(indx, right);
				balance(right);
			}
	}



	template<typename T>
	void Heap<T>::insert(const T &vl)
	{
		if (lenght == capacity)
			redist_memory();

		int i = lenght;
		int parent = (i - 1) / 2;
		arr[i] = vl;

		while (parent >= 0 && i > 0)
		{
			if (arr[i] > arr[parent])
				swap(i, parent);
			else
				break;

			i = parent;
			parent = (i - 1) / 2;
		}
		++lenght;
	}
	
	template<typename T>
	const T& Heap<T>::remove()
	{
		if (isEmpty()) throw 1;

		T max = arr[0];
		arr[0] = arr[--lenght];
		balance(0);
		return max;
	}



	template<typename T>
	void Heap<T>::outHeap() const noexcept
	{
		std::cout << "\n\n";

		int i = 0, k = 1;
		int tabs = lenght * 2 + 10;

		while (i < lenght) {

			for (int j = 0; j < tabs; ++j)
				std::cout << ' ';

			while ((i < k) && (i < lenght)) {

				std::cout << arr[i];

				if (arr[i] < 10)
					std::cout << ' ';

				for (int j = 0; j < tabs * 2; ++j)
					std::cout << ' ';

				++i;
			}
			std::cout << std::endl;
			tabs /= 2;
			k = k * 2 + 1;
		}
	}
	
	template<typename T>
	void Heap<T>::outArray() const noexcept
	{
		for (int i = 0; i < lenght; ++i)
			std::cout << arr[i] << '\t';
		std::cout << std::endl;
	}
	
	template<typename T>
	T* Heap<T>::getSortArray() const noexcept
	{
		Heap<T> heap(*this);
		T *sort_array = new T[lenght];

		for (int i = 0; i < lenght; ++i)
			sort_array[i] = heap.remove();

		return sort_array;
	}
}