#include "Observer.h"
#include <iostream>
#include <vector>



class ConcreateObserver: public algs::Observer
{
public:
	ConcreateObserver() = default;
	~ConcreateObserver() = default;

	void update(const std::string &message) override;
};

class ConcreateSubject: public algs::Subject
{
private:
	std::string message;

public:
	ConcreateSubject(const std::string &mes): message(mes) 
	{
	};
	~ConcreateSubject();

	void attach(algs::Observer*) override;
	void detach(algs::Observer*) override;
	void notify() override;

};



void ConcreateObserver::update(const std::string &message) {
	std::cout << "Observer update!\tMessage: " << message << '\n';
}

ConcreateSubject::~ConcreateSubject() {
	for (auto *i: observers) {
		delete i;
	}
}

void ConcreateSubject::attach(algs::Observer *observer) {
	observers.push_back(observer);
}

void ConcreateSubject::detach(algs::Observer *observer) {
	observers.remove(observer);
}

void ConcreateSubject::notify() {
	for (auto *i: observers) {
		i->update(message);
	}
}




int main()
{
	ConcreateObserver *observer = new ConcreateObserver;
	ConcreateSubject *subject1 = new ConcreateSubject("From subject sas");
	ConcreateSubject *subject2 = new ConcreateSubject("From subject sys");


	int len1 = 15, len2 = 10;
	std::vector<algs::Observer *> buff(len2 / 2);

	for (int i = 0; i < len1; ++i) {
		subject1->attach(new ConcreateObserver);
	}
	for (int i = 0; i < len2; ++i) {
		auto *ptr = new ConcreateObserver;
		subject2->attach(ptr);
		if (i > len2 / 2) {
			buff.push_back(ptr);
		}
	}

	subject2->notify();
	
	for (auto *i: buff) {
		subject2->detach(i);
	}

	std::cout << '\n';
	subject2->notify();

	std::cout << '\n';
	subject1->notify();

	return 0;
}