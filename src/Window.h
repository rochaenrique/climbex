#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <array>
#include <functional>

#include "renderer/RenderObject.h"
#include "events/Event.h"

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
            : name("Climbex!!"), width(800), height(800)
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
            void OnEvent(const Event& e);

            GLFWwindow* m_Window = nullptr;
            bool m_Running = true;
            WindowOptions m_Options;
            std::array<std::unique_ptr<RenderObject>, 4> m_Objs{};

            using EventCallbackFN = std::function<void(const Event& e)>;
            EventCallbackFN EventCallback;
    };

}
