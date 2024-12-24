#include "matx.hpp"

#include <iostream>

int main() 
{ 
    cm::matx<int,2,3> A = {
        { 1, 2, 3 },
        { 4, 5, 6 }
    };

    cm::matx<int,3,2> B = {
        { 10, 11 },
        { 20, 21 },
        { 30, 31 },
    };

    std::cout << A << std::endl << B << std::endl;
    std::cout << A*B << std::endl;
}
