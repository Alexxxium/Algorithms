#pragma once
#include <functional>
#include <thread>
#include <queue>


namespace algs::fnct
{
	class BaseFunct
	{
	public:

		virtual void operator()() const = 0;
		virtual ~BaseFunct() = default;
	};


	template <class F, typename...Args>
	class Funct: public BaseFunct
	{
	private:

		const std::function<F> function;
		const std::tuple<Args...> arguments;

		Funct(Funct&&) = delete;
		Funct(const Funct&) = delete;

	public:

		~Funct() = default;
		Funct(const F &func, Args...args);

		void operator()() const override;
	};
}


namespace algs
{
	class WaiteQueue
	{
	private:

		std::thread *target = nullptr;
		std::queue<fnct::BaseFunct*> queue;

		WaiteQueue(WaiteQueue&&) = delete;
		WaiteQueue(const WaiteQueue&) = delete;

	public:

		WaiteQueue();
		~WaiteQueue();

		template<typename F, typename...Args>
		void push(const F &func, Args&&...args);

		void start();
		void waite();
	};
}

#include "WaiteQueue.inl"
