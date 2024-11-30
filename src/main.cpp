#include "Window.h"
#include "Log.h"
#include <string>

int main() 
{ 
    cbx::Log::Init("");
    for (int i = 0; i < 10; i++)
        CBX_LOG("Hello Climbex! {} times", i);

    cbx::Window window;
    window.Init();
    window.Run();
}
