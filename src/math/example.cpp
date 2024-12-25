#include "vec.hpp"

#include <iostream>

int main() 
{ 
    cm::vec v = { 1, 6, 0 };
    cm::vec w = { -2, 5, 0 };

    std::cout << v << std::endl;
    std::cout << w << std::endl;
    std::cout << v*w << std::endl;
    std::cout << cm::cross(v, w) << std::endl;
}
