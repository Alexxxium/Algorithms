namespace algs
{
	template<typename T, bool waite>
	WaiteQueue<T, waite>::WaiteQueue():
		target_thread(nullptr),
		stopFlag(false)
	{
	}

	template<typename T, bool waite>
	WaiteQueue<T, waite>::~WaiteQueue()
	{
		if (!queue.empty()) waiteAll();
	}

	template<typename T, bool waite>
	void WaiteQueue<T, waite>::startProcess()
	{
		while (!queue.empty()) {
			std::thread thr(queue.front());

			if (waite && stopFlag && queue.size() == 1) {
				thr.join();
			}
			else {
				waite ? thr.join() : thr.detach();
			}

			queue.pop();
		}
	}

	template<typename T, bool waite>
	void WaiteQueue<T, waite>::wrapper()
	{
		if (queue.size() == 1) {
			if (target_thread) {
				target_thread->join();
				delete target_thread;
			}
			target_thread = new std::thread(&WaiteQueue::startProcess, this);
		}
	}

	template<typename T, bool waite>
	void WaiteQueue<T, waite>::push(T *thread)
	{
		if (!thread) throw std::exception("Pointer is NULL!");

		queue.push(thread);
		wrapper();
	}

	template<typename T, bool waite>
	void WaiteQueue<T, waite>::push(std::function<T> &&thread)
	{
		queue.push(std::move(thread));
		wrapper();
	}

	template<typename T, bool waite>
	void WaiteQueue<T, waite>::push(const std::function<T> &thread)
	{
		queue.push(thread);
		wrapper();
	}

	template<typename T, bool waite>
	void WaiteQueue<T, waite>::waiteAll()
	{
		stopFlag = true;
		target_thread->join();
		delete target_thread;
		target_thread = nullptr;
		stopFlag = false;
	}
}