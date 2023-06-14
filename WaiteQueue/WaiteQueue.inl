#include "WaiteQueue.h"

namespace algs::fnct
{
	template<class F, typename ...Args>
	inline Funct<F, Args...>::Funct(const F &func, Args...args):
		function(func),
		arguments(args...)
	{
	}
	template<class F, typename ...Args>
	void Funct<F, Args...>::operator()() const
	{
		std::apply(function, arguments);
	}
}

namespace algs
{
	template<typename F, typename...Args>
	void WaiteQueue::push(const F &func, Args&&...args)
	{
		if (!func) throw std::exception("Funñtion pointer is null!");

		fnct::BaseFunct *item = new fnct::Funct<F, Args...>(func, args...);
		queue.push(item);

		if (queue.size() == 1) {
			if (target) {
				target->join();
				delete target;
			}
			target = new std::thread(&WaiteQueue::start, this);
		}
	}
}
