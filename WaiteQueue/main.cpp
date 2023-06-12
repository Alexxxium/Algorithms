#include <iostream>
#include "WaiteQueue.h"
#include <vector>
#include <string>

std::vector<std::string> g_vec;

void processes()
{
	static int start = 1;
	int prev = start++;

	std::cout << "Procces " << prev << " starting...\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));

	// some long process
	if (prev % 2 == 0) std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "Process " << prev << " end!\n";
	g_vec.push_back("Thread " + std::to_string(prev) + " end!");
}

void targetFunc()
{
	std::cout << "Start reading...\n";

	algs::WaiteQueue<void(), false> queue;

	for (int i = 0; i < 8; ++i) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if (i % 3 == 0) std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Add process!\n";
		queue.push(processes);
	}

	// waite method
	queue.waiteAll();

	for (int i = 0; i < 8; ++i) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if (i % 3 == 0) std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Add process!\n";
		queue.push(processes);
	}

	std::cout << "End reading, out of func!\n";

}	//waite method working here...




int main()
{
	targetFunc();
	std::cout << '\n';

	// ordered threads:
	for (const auto &i : g_vec) {
		std::cout << i << '\n';
	}

	return 0;
}