#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "VertexArray.h"
#include "Program.h"

namespace cbx { 

    struct WindowOptions { 
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

    class Window { 
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
            std::unique_ptr<VertexArray> vao = nullptr;
            std::unique_ptr<Program> program = nullptr;
    };

}
