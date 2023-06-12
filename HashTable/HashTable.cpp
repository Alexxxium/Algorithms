#include <iostream>
#include <random>
#include "HashTable.h"



void TestHashTable()
{
	std::cout << "Capcity:\t";
	int len;
	std::cin >> len;
	std::cout << "Press 0 to set random key - value\nPress another int button to write\n"
		"Chouse:\t";
	int chouse;
	std::cin >> chouse;



	algs::HashTable<int, char> table(len);

	if (!chouse)
		for (int i = 0; i < len; ++i)
			table.insert((rand() % 100), 'V');
	else {
		std::cout << "Writing keys:\n";
		for (int i = 0; i < len; ++i)
		{
			int key;
			std::cin >> key;
			table.insert(key, 'V');
		}
	}


	table.outTable();

	bool stop = false;
	while (!stop)
	{
		std::cout << "Opeartions:\n\n"
			"1 - insert\n"
			"2 - erase\n"
			"3 - clear\n"
			"4 - reserve\n"
			"5 - find\n"
			"0 - stop\n\n";

		int ch_case;
		std::cout << "Your operation:\n";
		std::cin >> ch_case;

		switch (ch_case)
		{
		case 1: {
			int key;
			std::string vl;
			std::cout << "\nkey - value:\n";
			std::cin >> key >> vl;

			table.insert(key, 'V');
			break;
		}
		case 2:
			std::cout << "\nerase to key:\t";
			int key;
			std::cin >> key;
			table.erase(key);
			break;

		case 3:
			table.clear();
			break;

		case 4:
			int sz;
			std::cin >> sz;
			break;

		case 5: {
			std::cout << "\nkey:\t";
			int key1;
			std::cin >> key1;

			auto res = table.find(key1);

			if (res != nullptr)
				std::cout << "\n\n||||| " <<
				res->key << ' ' << res->value << " |||||\n\n";
			else
				std::cout << "\n\n||||| NOT FOUND! |||||\n\n";
			break;
		}
		default:
			stop = true;
			break;
		}

		std::cout << "\n\nYour HashTable:\n\n";
		table.outTable();
	}

}



int main()
{
	TestHashTable();
}