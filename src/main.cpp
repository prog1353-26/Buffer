#include <iostream>
#include "Buffer.h"

void showBuff(const Buffer& b) {
    std::cout << "[";
    for (size_t i=0;i<b.size();++i) {
        std::cout << b[i] ;
        if(i+1<b.size()){
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main()
{
    std::cout << "Start demo" << std::endl;

    {
        Buffer a;
        Buffer b(10);
        b[5] = 73;

        a = b;

        showBuff(a);
        showBuff(b);


    }

    std::cout << "Made it to the end" << std::endl;
    return 0;
}
