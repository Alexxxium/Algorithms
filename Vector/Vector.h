#pragma once
#pragma warning(disable: 6385)
#pragma warning(disable: 6001)
#pragma warning(disable: 4244)

template <class T>
class Vector
{
private:

	T *arr;
	int size;
	int capacity,
		default_capacity = 2;
	const float redist = 1.5;


	void redist_memory(int new_capacity = 0);

	Vector(Vector&&) = delete;
	Vector(const Vector&) = delete;
	void operator= (Vector&&) = delete;
	void operator= (const Vector&) = delete;

public:

	explicit Vector(const int lenght = 0);
	void push_back(const T);
	void resize(const int);
	void outVector() noexcept;

	~Vector() noexcept { delete[] arr; }
	T& operator[](const T index) { return arr[index]; }
	bool is_empty() noexcept { return capacity == 0; }
};

template <typename T>
Vector<T>::Vector(const int lenght): size(0), capacity(lenght)
{
	if (lenght)
		arr = new T[capacity];
	else
		arr = nullptr;
}

template <typename T>
void Vector<T>::push_back(const T vl)
{
	if (size == capacity)
		redist_memory();

	arr[size] = vl;

	++size;
}

template <typename T>
void Vector<T>::resize(const int sz)
{
	if (sz == capacity)
		return;

	if (sz == size && capacity > size)
		redist_memory(sz);
	else if (sz < size)
	{
		size = sz;
		redist_memory(sz);
	}
	else if (sz > size)
	{
		redist_memory(sz);
		size = sz;
	}
}

template <typename T>
void Vector<T>::outVector() noexcept
{
	if (is_empty())
	{
		std::cout << "\nVector is empty!\n\n";
		return;
	}
	std::cout << '\n';
	for (int i = 1; i < size + 1; ++i)
	{
		std::cout << arr[i - 1] << '\t';
		if (i % 10 == 0)
			std::cout << '\n';
	}
	std::cout << "\n\n" << std::endl;
}

template <typename T>
void Vector<T>::redist_memory(int new_capacity)
{
	if (is_empty()) {
		arr = new T[default_capacity];
		capacity = default_capacity;
	}

	if (new_capacity)
		capacity = new_capacity;
	else
		capacity = capacity * redist;

	int *copy = new T[capacity];
	for (int i = 0; i < size; ++i)
		copy[i] = arr[i];

	for (int i = size; i < capacity; ++i)
		copy[i] = 0;

	delete[] arr;
	arr = copy;
}
