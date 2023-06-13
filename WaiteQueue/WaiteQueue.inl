#include "WaiteQueue.h"
namespace algs
{
	template<typename T, typename...Args>
	WaiteQueue<T, Args...>::~WaiteQueue() { 
		if (!funcs.empty()) waiteAll(); 
	}


	template<typename T, typename...Args>
	void WaiteQueue<T, Args...>::start() {
		while (!funcs.empty()) {
			const auto &func = funcs.front();
			const auto &args = funcs_args.front();

			applyTupleToFunction(func, args);

			funcs.pop();
			funcs_args.pop();
		}
	}
	template<typename T, typename...Args>
	void WaiteQueue<T, Args...>::push(const std::function<T> &func, std::tuple<Args...> tuple) {
		funcs.push(func);
		funcs_args.push(tuple);

		if (funcs.size() == 1) {
			if (target) {
				target->join();
				delete target;
			}
			target = new std::thread(&WaiteQueue::start, this);
		}
	}
	template<typename T, typename...Args>
	void WaiteQueue<T, Args...>::waiteAll() {
		std::cout << "Waite:\n";
		if (!target) return;
		target->join();
		delete target;
		target = nullptr;
	}
}
