#include "Window.h"
#include "Log.h"

int main() 
{ 
    cbx::Log::Init("");
    cbx::Log::Send("Hello Climbex!");

    cbx::Window window;
    window.Init();
    window.Run();
}
