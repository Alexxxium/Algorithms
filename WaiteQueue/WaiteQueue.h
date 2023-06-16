#pragma once
#include <functional>
#include <thread>
#include <queue>

namespace algs::fnct
{
	class Funct
	{
	public:

		virtual void operator()() const = 0;
		virtual ~Funct() = default;
	};

	template<class T, class R>
	class FunctWhith: public Funct
	{
	private:

		T functor;
		R &return_value;

		FunctWhith(FunctWhith&&) = delete;
		FunctWhith(const FunctWhith&) = delete;

	public:

		~FunctWhith() = default;
		FunctWhith(const T &funct, R &r_val);

		void operator()() const override;
	};

	template<class T>
	class FunctWhithout: public Funct
	{
	private:

		T functor;

		FunctWhithout(FunctWhithout&&) = delete;
		FunctWhithout(const FunctWhithout&) = delete;

	public:

		~FunctWhithout() = default;
		FunctWhithout(const T &funct);

		void operator()() const override;
	};
}

namespace algs
{
	class WaiteQueue
	{
	private:

		std::thread *target;
		std::queue<fnct::Funct*> queue;

		WaiteQueue(WaiteQueue&&) = delete;
		WaiteQueue(const WaiteQueue&) = delete;

		void start();
		void wrapper();

	public:

		~WaiteQueue();

		WaiteQueue();

		template<typename T, typename R>
		void push(const T &funct, R &r_val);

		template<typename T>
		void push(const T &funct);

		void waite();
	};
}

#include "WaiteQueue.inl"