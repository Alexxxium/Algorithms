#pragma once

#include <cstdint>
#include <iostream>

template<class T>
class RingBuffer
{
private:

	uint16_t lenght;

	T *buff;
	bool empty = true;
	int indexIn, indexOut;
	

	void toNext(int &index) { 
		index = ((index + 1) >= lenght ? 0 : (index + 1));
	}
	int  getCorrect(int index){
		return index >= lenght ? 0 : index;
	}

public:

	 RingBuffer(const int lenght);
	~RingBuffer() { delete[] buff; }


	void push(const T);
	void pop();


	bool isEmpty() { return empty;  }
	size_t size()  { return lenght; }

	int  top() {
		if (isEmpty()) throw 1;
		return indexIn == 0 ? buff[size() - 1] : buff[indexIn - 1];
	}


	RingBuffer& operator << (T vl)  { 
		push(vl); 
		return *this;
	}
	RingBuffer& operator >> (T &vl) {
		vl = buff[getCorrect(indexOut)];
		pop(); 
		return *this;
	}


	void clear();
	void outBuff();
};


template<typename T>
RingBuffer<T>::RingBuffer(const int lenght):
	lenght(lenght), indexIn(0), indexOut(-1), empty(true)
{
	if (lenght < 0) throw 1;

	buff = new int[lenght];

	for (int i = 0; i < lenght; ++i)
		buff[i] = T(0);
}


template<typename T>
void RingBuffer<T>::push(const T vl)
{
	empty = false;

	buff[getCorrect(indexIn)] = vl;

	if (getCorrect(indexIn) == indexOut)	// перезапись
		toNext(indexOut);

	toNext(indexIn);

	if (indexOut == -1)						// -1 означает первую запись, в том числе и после очистки буфера
		indexOut = 0;
}
template<typename T>
void RingBuffer<T>::pop()
{
	buff[getCorrect(indexOut)] = T(0);
	toNext(indexOut);

	if (indexOut == indexIn)				// удалился последний элемент
		clear();
}
template<typename T>
void RingBuffer<T>::clear()
{
	for (int i = 0; i < lenght; ++i) buff[i] = T(0);	// зануление для удобства

	indexOut = -1;
	indexIn = 0;
	empty = true;
}
template<typename T>
void RingBuffer<T>::outBuff()
{
	for (int i = 0; i < lenght; ++i)
		std::cout << buff[i] << '\t';
	std::cout << std::endl;
}