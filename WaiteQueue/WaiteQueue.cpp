#include "WaiteQueue.h"

namespace algs
{
	WaiteQueue::~WaiteQueue() {
		waite();
	}

	WaiteQueue::WaiteQueue():
		target(nullptr)
	{
	}

	void WaiteQueue::start() {
		while (!queue.empty()) {
			const auto &func = *(queue.front());
			func();
			delete &func;
			queue.pop();
		}
	}
	void WaiteQueue::wrapper() {
		if (queue.size() == 1) {
			if (target) {
				target->join();
				delete target;
			}
			target = new std::thread(&WaiteQueue::start, this);
		}
	}
	void WaiteQueue::waite() {
		if (target) {
			target->join();
			delete target;
			target = nullptr;
		}
	}
}