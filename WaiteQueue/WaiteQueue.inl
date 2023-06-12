#include "WaiteQueue.h"
namespace algs
{
	template<typename T>
	WaiteQueue<T>::WaiteQueue():
		target_thread(nullptr)
	{
	}

	template<typename T>
	WaiteQueue<T>::~WaiteQueue()
	{
		if (!queue.empty()) waiteAll();
	}

	template<typename T>
	void WaiteQueue<T>::startProcess()
	{
		while (!queue.empty()) {
			queue.front()();
			queue.pop();
		}
	}

	template<typename T>
	void WaiteQueue<T>::wrapper()
	{
		if (queue.size() == 1) {
			if (target_thread) {
				target_thread->join();
				delete target_thread;
			}
			target_thread = new std::thread(&WaiteQueue::startProcess, this);
		}
	}

	template<typename T>
	void WaiteQueue<T>::push(T *thread)
	{
		if (!thread) throw std::exception("Pointer is NULL!");

		queue.push(thread);
		wrapper();
	}

	template<typename T>
	void WaiteQueue<T>::push(std::function<T> &&thread)
	{
		queue.push(std::move(thread));
		wrapper();
	}

	template<typename T>
	void WaiteQueue<T>::push(const std::function<T> &thread)
	{
		queue.push(thread);
		wrapper();
	}

	template<class T>
	auto& WaiteQueue<T>::operator<<(T *thread)
	{
		push(thread);
		return *this;
	}

	template<class T>
	auto& WaiteQueue<T>::operator<<(std::function<T> &&thread)
	{
		push(std::move(thread));
		return *this;
	}

	template<class T>
	auto& WaiteQueue<T>::operator<<(const std::function<T> &thread)
	{
		push(thread);
		return *this;
	}

	template<typename T>
	void WaiteQueue<T>::waiteAll()
	{
		target_thread->join();
		delete target_thread;
		target_thread = nullptr;
	}
}
