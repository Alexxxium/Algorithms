
#include <iostream>
#include "Stack.h"
#include <random>


void Message()
{
    std::cout <<
        "\n1 -- push\n" <<
        "2 -- pop\n" <<
        "3 -- top\n" <<
        "0 -- Quit\n" <<
        "Command:\t";
}

void TestStack()
{
    algs::Stack<int> stack;

    int command, value;

    bool stop = false;

    while (!stop)
    {
    sas:
        Message();
        std::cin >> command;

        switch (command)
        {
        case 1:
            std::cout << "Push:\t";
            std::cin >> value;
            stack.push(value);
            break;
        case 2:
            stack.remove();
            break;
        case 3:
            std::cout << "\n\n\nTop:\t---> " << stack.top() << " <---\n\n\n";
            break;
        case 0:
            stop = true;
            break;

        default:
            goto sas;
            break;
        }
        std::cout << "\nStack:\n";
        stack.outStack();
    }
}




int main()
{
    TestStack();
}


