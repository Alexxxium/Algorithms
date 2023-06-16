#include <iostream>
#include "WaiteQueue.h"


std::vector<std::string> g_vec;
std::vector<int> g_res;


struct Test
{
	void test1(int a) {
		std::cout << "(void)\t\t\tTest::test1 -> starting...\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "End ->\t\t\tTest::test1!\n";
		g_vec.push_back("Thread (method) 1");
	}

	int test2(int a, int &b) {

		std::cout << "(int)\t\t\tTest::test2 -> starting...\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "End ->\t\t\tTest::test2!\n";
		g_vec.push_back("Thread (method) 2");

		return a + b;
	}

	const int& test3(int &&a, const int &b, int &c) {
		std::cout << "(const int&)\t\tTest::test3 -> starting...\n";
		std::this_thread::sleep_for(std::chrono::seconds(4));
		std::cout << "End ->\t\t\tTest::test3!\n";
		g_vec.push_back("Thread (method) 3");

		return a + b + c;
	}

	static int* test4(int *a, const int *b) {
		std::cout << "(static)\t\tTest::test4 -> starting...\n";
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::cout << "End ->\t\t\tTest::test4!\n";
		g_vec.push_back("Thread (method) 4");

		return new int(*a + *b);
	}

	void test5() {
		std::cout << "(void)\t\t\tTest::test5 -> starting....\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "End ->\t\t\tTest::test5!\n";
		g_vec.push_back("Thread (method) 5");
	}
};


void testing()
{
	algs::WaiteQueue queue;
	Test obj;
	g_res.resize(2);

	std::cout << "\tStart Reading...\n\n";

	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Add new function!\n";
	{
		// using std::bind()
		const auto &func = std::bind(&Test::test1, &obj, 12);
		queue.push(func);
	}


	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Add new function!\n";
	{
		int arg1 = 10;

		// std::bind() whith correct args (you can use std::ref, std::cref)
		const auto &func = std::bind(&Test::test2, &obj, 12, std::ref(arg1));

		// g_res[0] this is not const reference which stores the result
		queue.push(func, g_res[0]);
	}

	// You can waite all functions
	std::cout << "\n\tUser\'s waiting...\n";
	queue.waite();
	std::cout << "\tEnd waiting!\n\n";

	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Add new function!\n";
	{
		int arg1 = 5, arg2 = 8;

		// using lambda-function (recommend to use, if you want hand over r-value arg/args)
		const auto &func = [&]() { return obj.test3(std::move(arg1), 12, arg2); };
		queue.push(func, g_res[1]);
	}


	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Add new function!\n";
	{
		const auto &func = std::bind(Test::test4, new int(4), new int(6));

		// return value is missing!
		queue.push(func);
	}

	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Add new function!\n";
	{
		// lambda function instead std::bind
		const auto &func = [&]() { obj.test5(); };
		queue.push(func);
	}

	std::cout << "\n\tWaiting working...\n\n";

}	// Waiting working here!


int main()
{
	testing();

	std::cout << "\nVector:\n";
	for (const auto &i : g_vec)
		std::cout << i << '\n';

	std::cout << "\n\nResults:\n";
	for (const auto &i : g_res)
		std::cout << i << '\n';
}