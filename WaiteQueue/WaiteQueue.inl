namespace algs::fnct
{
	template<class T, class R>
	inline FunctWhith<T, R>::FunctWhith(const T &funct, R &r_val):
		functor(funct),
		return_value(r_val)
	{
	}
	template<class T>
	inline FunctWhithout<T>::FunctWhithout(const T &funct):
		functor(funct)
	{
	}

	template<class T, class R>
	void FunctWhith<T, R>::operator()() const {
		return_value = functor();
	}
	template<class T>
	void FunctWhithout<T>::operator()() const {
		functor();
	}
}

namespace algs
{
	template<typename T, typename R>
	void WaiteQueue::push(const T &funct, R &r_val) {
		fnct::Funct *item = new fnct::FunctWhith<T, R>(funct, r_val);
		queue.push(item);

		wrapper();
	}

	template<typename T>
	void WaiteQueue::push(const T &funct) {
		fnct::Funct *item = new fnct::FunctWhithout<T>(funct);
		queue.push(item);

		wrapper();
	}
}