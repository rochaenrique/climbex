#include "Window.h"
#include "Log.h"
#include <string>

int main() 
{ 
    cbx::Log::Init("");

    cbx::Window window;
    window.Init();
    window.Run();
}
