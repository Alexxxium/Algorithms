#pragma once

#include <cstdint>
#include <iostream>

namespace algs
{
	template<class T>
	class RingBuffer
	{
	private:

		uint16_t lenght;

		T *buffer;
		bool empty = true;
		int indexIn, indexOut;


	public:

		explicit RingBuffer(const int lenght);

		RingBuffer(RingBuffer<T>&&) noexcept;
		RingBuffer(const RingBuffer<T>&) noexcept;

		void operator= (RingBuffer<T>&&) noexcept;
		void operator= (const RingBuffer<T>&) noexcept;

		~RingBuffer() noexcept { delete[] buffer; }


	private:

		inline void toNext(int &index) const noexcept;
		inline int  getCorrect(int index) const noexcept;


	public:

		void insert(const T&) noexcept;
		void remove();


		bool isEmpty() const noexcept { return empty; }
		size_t size()  const noexcept { return lenght; }

		const T& top() const;


		auto& operator << (const T &vl) noexcept;
		auto& operator >> (T &vl) noexcept;


		void clear() noexcept;
		void outBuff() const noexcept;
	};
}

#include "RingBuffer.inl"
