
#include "Heap.h"
#include <random>


void TestHeap()
{
    std::cout << "Enter capcity (size):\t";
    int capacity;
    std::cin >> capacity;
    std::cout << "Input \"0\" if you want get random heap\n" <<
        "or input another intenger button\nYour chouse:\t";

    algs::Heap<int> heap(capacity);

    int start;
    std::cin >> start;

    for (int i = 0; i < capacity; ++i)
    {
        if (start)
        {
            int vl;
            std::cin >> vl;
            heap.insert(vl);
        }
        else
            heap.insert(rand() % 100);
    }

    std::cout << "Your heap:\n" << "\nArray:\n\t";
    heap.outArray();
    std::cout << "\n\nHeap:\n";
    heap.outHeap();
    std::cout << '\n' << std::endl;

    int operation = 1;
    while (operation)
    {

        std::cout << "Operations:\n" <<
            "1 <- push\n" <<
            "2 <- get sort array\n" <<
            "3-9 <- pop\n" <<
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
            heap.insert(vl);
            break;
        case 2:
            std::cout << "Your sort array:\t";
            int *sort;                                     // тип данных указать явно
            sort = heap.getSortArray();
            for (int i = 0; i < heap.size(); ++i)
                std::cout << sort[i] << ' ';
            delete[] sort;
        case 0:
            break;

        default:
            std::cout << "\nPop():\t" <<
                heap.remove() << '\n' << "\n\n";
            break;
        }
        std::cout << "\n////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
        std::cout << "Your heap:\n" << "\nArray:\n\t";
        heap.outArray();
        std::cout << "\n\nHeap:\n";
        heap.outHeap();
        std::cout << '\n' << std::endl;
    }


}



int main()
{
    TestHeap();
}


