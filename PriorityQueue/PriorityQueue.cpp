
#include <iostream>
#include "PriorityQueue.h"

void TestQueque()
{
    std::cout << "Enter capcity (size):\t";
    int capacity;
    std::cin >> capacity;
    std::cout << "Input \"0\" if you want get random queue\n" <<
        "or input another intenger button\nYour chouse:\t";

    PriorityQueue<int> queue(capacity);

    int start;
    std::cin >> start;

    for (int i = 0; i < capacity; ++i)
    {
        if (start)
        {
            int vl;
            std::cin >> vl;
            queue.push(vl);
        }
        else
            queue.push(rand() % 100);
    }

    std::cout << "\n\nQueue:\n";
    queue.out();
    std::cout << '\n' << std::endl;

    int operation = 1;
    while (operation)
    {

        std::cout << "Operations:\n" <<
            "1 <- push\n" <<
            "2-9 <- pop\n" <<
            "0 <- stop\n" <<
            "Operation:\t";
        std::cin >> operation;

        std::cout << "\n////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
        switch (operation)
        {
        case 1:
            int vl;
            std::cout << "Push():\t";
            std::cin >> vl;
            queue.push(vl);
            break;
        case 0:
            break;

        default:
            std::cout << "\nPop():\t" <<
                queue.pop() << '\n' << "\n\n";
            break;
        }
        std::cout << "\n////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
        std::cout << "Your queue:\n";
        queue.out();
        std::cout << '\n' << std::endl;
    }


}

int main()
{
    TestQueque();
}
