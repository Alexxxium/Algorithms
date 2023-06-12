
#include "LinkList.h"
#include <random>


void Message()
{
    std::cout <<
        "\n1 -- push_back\n" <<
        "2 -- push_front\n" <<
        "3 -- pop_back\n" <<
        "4 -- pop_front\n" <<
        "5 -- insert (index)\n" <<
        "6 -- pop_insert (index)\n" <<
        "0 -- Quit\n\n"
        "Command:\t";
}

void TestLinkList()
{
    algs::LinkList<int> list;

    int command, value, index;

    bool stop = false;

    while (!stop)
    {
    sas:
        Message();
        std::cin >> command;

        switch (command)
        {
        case 1:
            std::cout << "Push_back:\t";
            std::cin >> value;
            list.push_back(value);
            break;
        case 2:
            std::cout << "Push_front:\t";
            std::cin >> value;
            list.push_front(value);
            break;
        case 3:
            list.pop_back();
            break;
        case 4:
            list.pop_front();
            break;
        case 5:
            std::cout << "Index:\t";
            std::cin >> index;
            std::cout << "Value:\t";
            std::cin >> value;
            list.insert(index, value);
            break;
        case 6:
            std::cout << "Index:\t";
            std::cin >> index;
            list.pop_insert(index);
            break;
        case 0:
            stop = true;
            break;

        default:
            goto sas;
            break;
        }
        std::cout << "\nList:\n";
        list.outLinkList();
    }
}




int main()
{
    TestLinkList();
}



