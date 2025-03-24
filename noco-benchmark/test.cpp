#include <iostream>

#ifdef X64BIT
#    define VAR_TYPE unsigned long long
#else
#    define VAR_TYPE unsigned int
#endif

#ifndef MULT
#    define MULT 1
#endif


int main() {
    VAR_TYPE value = 0;
    VAR_TYPE buffer = 0;

    std::cout<<"Size of buffer: "<<sizeof(buffer)<<std::endl;
    std::cout<<"Multiplier: "<<MULT<<std::endl;

    for (value = 0; value < 100000000 * MULT; value++)
        buffer += value;

    std::cout<<buffer<<std::endl;

    return 0;
}
