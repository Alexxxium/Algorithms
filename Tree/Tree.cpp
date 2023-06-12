

#include <iostream>
#include <random>
#include "Tree.h"



void TestTree()
{
	algs::Tree<int> tree;
	size_t size;
	int start;

	std::cout << "Enter a lenght (only intenger button):\t";
	std::cin >> size;

	std::cout << "Input 0 if you want write values or press another button:\t";
	std::cin >> start;

	int curr;
	if (start)
		for (int i = 0; i < size; ++i)
		{
			curr = rand() % 100;
			tree.insert(curr);
		}
	else
		for (int i = 0; i < size; ++i)
		{
			std::cin >> curr;
			tree.insert(curr);
		}

	std::cout << "\nYour tree:\n";
	tree.outTree();

	while (true)
	{
		static size_t it(0);
		++it;
		char stop;
		std::cout << "Opeations:\n\n" <<
			"delete value -> press 0\n" <<
			"insert value -> press 1\n" <<
			"Quit -> press \'q\'\n\n" <<
			"Your operation:\t";

		std::cin >> stop;
		if (stop == 'q' || stop == 'Q') break;

		curr = stop - '0';

		if (curr)
		{
			std::cout << "\ninsert:\t";
			std::cin >> curr;
			tree.insert(curr);
		}
		else
		{
			std::cout << "\ndelete:\t";
			std::cin >> curr;
			tree.remove(curr);
		}

		tree.outTree();
	}
}




int main()
{
	TestTree();
}


