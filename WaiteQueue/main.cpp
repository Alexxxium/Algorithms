#include <iostream>
#include "WaiteQueue.h"


std::vector<std::string> g_vec;
std::string str = "sas";


void test1(int a) {

    std::cout << "Starting thread 1...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "end thread 1\n";
    g_vec.push_back("Thread 1 end!");
}

int test2(std::string &s) {

    s = "sys";
    std::cout << "Starting thread 2...\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "end thread 2\n";
    g_vec.push_back("Thread 2 end!");

    return 0;
}

const int* test3(int a, double b, float c) {

    std::cout << "Starting thread 3...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "end thread 3\n";
    g_vec.push_back("Thread 3 end!");

    return new int;
}

int test4() {

    std::cout << "Starting thread 4...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "end thread 4\n";
    g_vec.push_back("Thread 4 end!");

    return 0;
}

const std::string& test5(int *) {

    std::cout << "Starting thread 5...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "end thread 5\n";
    g_vec.push_back("Thread 5 end!");

    return "sas";
}



void tests() {

    algs::WaiteQueue queue;

    std::cout << "Start reading...\n\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Add new function!\n";
    queue.push(test1, 12);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Add new function!\n";
    queue.push(test2, str);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Add new function!\n";
    queue.push(test3, 12, 12.4, 3.14);

    std::cout << "\nUser\'s waiting...:\n";

    // You can waite all functions
    queue.waite();
    std::cout << "End wait!\n\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Add new function!\n";
    queue.push(test4);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Add new function!\n";
    queue.push(test5, new int);

    std::cout << "\nWaiting working here!\n\n";

}   // Queue waite all functions here!



int main()
{
    tests();

    std::cout << "\nArg&:\t" << str << "\n\n";

    for (const auto &i : g_vec)
        std::cout << '\n' << i;

}