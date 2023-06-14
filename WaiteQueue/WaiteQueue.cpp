#include "WaiteQueue.h"

namespace algs
{
	WaiteQueue::WaiteQueue():
		target(nullptr)
	{
	}

	WaiteQueue::~WaiteQueue() {
		waite();
	}

	void WaiteQueue::start() {
		while (!queue.empty()) {
			const auto &func = *(queue.front());
			func();
			delete &func;
			queue.pop();
		}
	}

	void WaiteQueue::waite() {
		if (target) {
			target->join();
			delete target;
		}
		target = nullptr;
	}
}
