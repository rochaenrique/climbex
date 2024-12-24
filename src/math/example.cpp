#include "matx.hpp"
#include "vec.hpp"

#include <iostream>

int main() 
{ 
    cm::matx<int,2,2> A = {
        { 1, 2 },
        { 3, 4 }
    };

    cm::matx<int,2,2> B = {
        { 5, 6 },
        { 7, 8 }
    };

    std::cout << A << std::endl << B << std::endl;

    std::cout << A * B << std::endl;
}
