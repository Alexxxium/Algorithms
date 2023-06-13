#pragma once
#include <functional>
#include <thread>
#include <queue>
#include <tuple>


namespace algs
{
	template <class T, typename... Args>
	class WaiteQueue
	{
	private:

		std::queue<std::function<T>> funcs;
		std::queue<std::tuple<Args...>> funcs_args;
		std::thread *target = nullptr;

	public:

		~WaiteQueue();
		void start();
		void push(const std::function<T> &func, std::tuple<Args...> tuple);
		void waiteAll();


		template <typename Function, typename Tuple, std::size_t... Indices>
		decltype(auto) applyTupleToFunction(Function&& func, Tuple&& tuple, std::index_sequence<Indices...>) {
			return std::invoke(std::forward<Function>(func), std::get<Indices>(std::forward<Tuple>(tuple))...);
		}

		template <typename Function, typename... Aargs>
		decltype(auto) applyTupleToFunction(Function&& func, const std::tuple<Aargs...>& tuple) {
			constexpr std::size_t tupleSize = sizeof...(Args);
			return applyTupleToFunction(std::forward<Function>(func), tuple, std::make_index_sequence<tupleSize>());
		}
	};
}

#include "WaiteQueue.inl"
