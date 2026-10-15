#include <iostream>
#include "Buffer.h"



int main()
{
    std::cout << "Start demo" << std::endl;

    {
        Buffer a;
        Buffer b(10);

        b[5] = 73;

        std::cout << b[5] << std::endl;

    }

    std::cout << "Made it to the end" << std::endl;
    return 0;
}
