#pragma once
#include <functional>
#include <thread>
#include <queue>


namespace algs
{
	template <class T, bool waite>
	class WaiteQueue
	{
	private:

		std::queue<std::function<T>> queue;
		std::thread *target_thread;
		bool stopFlag;

		void startProcess();
		void wrapper();

	public:

		WaiteQueue();
		~WaiteQueue();

		WaiteQueue(WaiteQueue&&) = delete;
		WaiteQueue(const WaiteQueue&) = delete;

		void push(T *thread);
		void push(std::function<T> &&thread);
		void push(const std::function<T> &thread);

		void waiteAll();
	};
}

#include "WaiteQueue.inl"
