
#include <iostream>
#include "Vector.h"


void Message()
{
    std::cout <<
        "\n1 -- push_back\n" <<
        "2 -- resize (lenght)\n" <<
        "0 -- Quit\n" <<
        "Command:\t";
}
void TestVector()
{
    Vector<int> vec;

    int command, value, size;

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
            vec.push_back(value);
            break;
        case 2:
            std::cout << "Resize:\t";
            std::cin >> size;
            vec.resize(size);
            break;
        case 0:
            stop = true;
            break;

        default:
            goto sas;
            break;
        }
        std::cout << "\nVector:\n";
        vec.outVector();
    }
}



int main()
{
    TestVector();
}


