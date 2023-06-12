
namespace algs
{
	template<typename T>
	RingBuffer<T>::RingBuffer(const int lenght):
		lenght(lenght),
		indexIn(0),
		indexOut(-1),
		empty(true)
	{
		if (lenght < 0) throw 1;

		buffer = new int[lenght];

		for (int i = 0; i < lenght; ++i)
			buffer[i] = T();
	}


	template<typename T>
	RingBuffer<T>::RingBuffer(RingBuffer<T> &&buff) noexcept:
		empty(buff.empty),
		lenght(buff.lenght),
		indexIn(buff.indexIn),
		indexOut(buff.indexOut)
	{
		delete buffer;
		buffer = buff.buffer;

		buff.buffer = nullptr;
		buff.empty = true;
		buff.lenght = 0;
		buff.indexIn = 0;
		buff.indexOut - 1;
	}

	template<typename T>
	RingBuffer<T>::RingBuffer(const RingBuffer<T> &buff) noexcept:
		empty(buff.empty),
		lenght(buff.lenght),
		indexIn(buff.indexIn),
		indexOut(buff.indexOut)
	{
		delete buffer;
		buffer = new T[lenght];

		for (int i = 0; i < lenght; ++i)
			buffer[i] = buff.buffer[i];
	}

	template<typename T>
	void RingBuffer<T>::operator = (RingBuffer<T> &&buff) noexcept
	{
		if (this == &buff) return;

		empty = buff.empty;
		lenght = buff.lenght;
		indexIn = buff.indexIn;
		indexOut = buff.indexOut;

		delete buffer;
		buffer = buff.buffer;

		buff.buffer = nullptr;
		buff.empty = true;
		buff.lenght = 0;
		buff.indexIn = 0;
		buff.indexOut - 1;
	}

	template<typename T>
	void RingBuffer<T>::operator = (const RingBuffer<T> &buff) noexcept
	{
		if (this == &buff) return;

		empty = buff.empty;
		lenght = buff.lenght;
		indexIn = buff.indexIn;
		indexOut = buff.indexOut;

		delete buffer;
		buffer = new T[lenght];

		for (int i = 0; i < lenght; ++i)
			buffer[i] = buff.buffer[i];
	}



	template<typename T>
	const T& RingBuffer<T>::top() const
	{
		if (isEmpty()) throw 1;
		return indexIn == 0 ? buffer[size() - 1] : buffer[indexIn - 1];
	}



	template<typename T>
	auto& RingBuffer<T>::operator << (const T &vl) noexcept
	{
		insert(vl);
		return *this;
	}
	
	template<typename T>
	auto& RingBuffer<T>::operator >> (T &vl) noexcept
	{
		if (indexOut == -1)
			vl = T();
		else {
			vl = buffer[getCorrect(indexOut)];
			remove();
		}

		return *this;
	}



	template<typename T>
	void RingBuffer<T>::toNext(int &index) const noexcept
	{
		index = ((index + 1) >= lenght ? 0 : (index + 1));
	}

	template<typename T>
	int  RingBuffer<T>::getCorrect(int index) const noexcept
	{
		return index >= lenght ? 0 : index;
	}



	template<typename T>
	void RingBuffer<T>::insert(const T &vl) noexcept
	{
		empty = false;

		buffer[getCorrect(indexIn)] = vl;

		if (getCorrect(indexIn) == indexOut)
			toNext(indexOut);

		toNext(indexIn);

		if (indexOut == -1)
			indexOut = 0;
	}
	
	template<typename T>
	void RingBuffer<T>::remove()
	{
		if (empty) throw 1;
		buffer[getCorrect(indexOut)] = T();
		toNext(indexOut);

		if (indexOut == indexIn)
			clear();
	}
	
	template<typename T>
	void RingBuffer<T>::clear() noexcept
	{
		for (int i = 0; i < lenght; ++i) buffer[i] = T();

		indexOut = -1;
		indexIn = 0;
		empty = true;
	}
	
	template<typename T>
	void RingBuffer<T>::outBuff() const noexcept
	{
		for (int i = 0; i < lenght; ++i)
			std::cout << buffer[i] << '\t';
		std::cout << std::endl;
	}
}