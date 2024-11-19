#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <array>

#include "RenderObject.h"
#include "Program.h"

namespace cbx { 

    struct WindowOptions 
    { 
        std::string name;
        unsigned int width;
        unsigned int height;

        WindowOptions(std::string name, 
                unsigned int width,
                unsigned int height) 
            : name(name), width(width), height(height)
        {} 

        WindowOptions() 
            : name("Climbex!!"), width(640), height(480)
        {}

    };

    class Window 
    { 
        public: 
            Window(WindowOptions opt = WindowOptions());
            ~Window();

            void Init();
            void Run();

        private: 
            void OnUpdate();

            GLFWwindow* m_Window = nullptr;
            bool m_Running = true;
            WindowOptions m_Options;
            std::array<std::unique_ptr<RenderObject>, 6> objs{};
    };

}
