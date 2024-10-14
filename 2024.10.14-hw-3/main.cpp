#include <iostream>
#include "string.h"

int main()
{
    String const hello("hello"); 

    std::cout << "String const hello(\"hello\");\n" << std::endl;
    std::cout << "std::cout << hello[0][4] << std::endl;" << std::endl;

    std::cout << hello[0][4] << "\n\n";

    std::cout << "std::cout << hello[1][4] << std::endl;" << std::endl;

    std::cout << hello[1][4] << "\n\n";

    std::cout << "std::cout << hello[3][3] << std::endl;" << std::endl;

    std::cout << hello[3][3] << "\n\n";

    std::cout << "std::cout << hello[2][3] << std::endl;" << std::endl;

    std::cout << hello[2][3] << "\n\n";

    return 0;
}