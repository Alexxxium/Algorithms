#include <list>
#include <string>


namespace algs
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void update(const std::string&) = 0;
	};
	
	class Subject
	{
	protected:
		std::list<Observer*> observers;

	public:
		virtual ~Subject() = default;
		virtual void attach(Observer*) = 0;
		virtual void detach(Observer*) = 0;
		virtual void notify() = 0;
	};
}