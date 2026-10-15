#include <iostream>
#include "Buffer.h"



int main()
{
    std::cout << "Start demo" << std::endl;

    {
        Buffer a(10);
        a[0] = 55;
        std::cout << a[0] << std::endl;
    }

    std::cout << "Made it to the end" << std::endl;
    return 0;
}
