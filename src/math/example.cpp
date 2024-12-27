#include <iostream>

#include "ppmath.hpp"

int main() 
{ 
    //auto trans_mat = cm::transl(cm::vec(1.0f, 1.0f, 0.0f));
    auto trans_mat = cm::scale<float, 3>(0.5f);

    std::cout << trans_mat*cm::vec(2.0f, 3.0f, 0.0f) << std::endl;
}
