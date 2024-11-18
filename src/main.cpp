#include "Window.h"
#include <iostream>

int main() 
{ 
    std::cout << "Hello Climbex!\n";

    cbx::Window window;
    window.Init();
    window.Run();

}
