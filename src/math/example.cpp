#include <iostream>

#include "ppmath.hpp"

int main() 
{ 
    cm::matx<int,3> A = {{ { 4, 2, 0 }, 
        { 0, 8, 1 }, 
        { 0, 1, 0 }, 
    }};
    cm::matx<int,3> B = {{ 
        { 4, 2, 1 }, 
        { 2, 0, 4 }, 
        { 9, 4, 2 }, 
    }};

    auto I = cm::make_iden<int,4>();
    cm::vec<int,4> x(1, 2, 3, 4);

    std::cout << I*x << std::endl;

}
