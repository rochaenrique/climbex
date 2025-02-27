#include "Window.h"
#include "ResourceManager.h"
#include "Log.h"

#include "renderer/VertexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Program.h"
#include "renderer/Shader.h"

#include "events/MouseEvents.h"
#include "events/KeyEvents.h"
#include "events/WindowEvents.h"

#include "math/vec.hpp"

#include <iostream>

cbx::Window::Window(WindowOptions opt)
    : m_Options(opt)
{
    EventCallback = [this](const Event& e) { OnEvent(e); };
};

cbx::Window::~Window()
{
    glfwTerminate();
};

void cbx::Window::Init()
{
    if (!glfwInit()) 
    { 
        std::cout << "ERROR\n";
        m_Running = false;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    m_Window = glfwCreateWindow(m_Options.width, m_Options.height, m_Options.name.c_str(), NULL, NULL);

    if (!m_Window) 
    { 
        std::cout << "ERROR\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Window);

    if (GLenum err = glewInit() != GLEW_OK) { 
        std::cout << "Error while initializing glew: " << glewGetErrorString(err) << std::endl;
        return;
    }

    glfwSetWindowUserPointer(m_Window, this);

#ifndef CBX_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](GLenum source, 
                GLenum type, 
                GLuint id, 
                GLenum severity, 
                GLsizei length, 
                const GLchar* message, 
                const void* userParam) { 
            //TODO: Properly format a send message
            //CBX_LOG(message);
            }, 0);
#endif

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) { 
            Window* usrWindow = (Window*)glfwGetWindowUserPointer(window);
            usrWindow->m_Running = false;
            });

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) { 
            //std::cout << "WINDOW SIZE EVENT: " << width << "x" << height << std::endl;
            Window* usrWindow = (Window*)glfwGetWindowUserPointer(window);
            usrWindow->EventCallback(WindowResizeEvent(width, height));
            });

    //key events
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { 
            Window* usrWindow = (Window*)glfwGetWindowUserPointer(window);
            switch (action) 
            { 
                case GLFW_PRESS:
                    usrWindow->EventCallback(KeyPressEvent(key, scancode));
                    break;
                case GLFW_RELEASE:
                    usrWindow->EventCallback(KeyReleaseEvent(key, scancode));
                    break;
                default: 
                    std::cout << "Key Event is neither PRESS or RELEASE!\n";
                    break;
            }
            });

    //mouse move events
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) { 
            Window* usrWindow = (Window*)glfwGetWindowUserPointer(window);
            usrWindow->EventCallback(MouseMoveEvent(xpos, ypos));
            });

    //mouse button events
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) { 
            //std::cout << "MOUSE BUTTON EVENT: " << button << ", " << action << ", " << mods << std::endl;
            Window* usrWindow = (Window*)glfwGetWindowUserPointer(window);
            switch (action) 
            { 
                case GLFW_PRESS:
                    usrWindow->EventCallback(MouseButtonPressEvent(button));
                    break;
                case GLFW_RELEASE:
                    usrWindow->EventCallback(MouseButtonReleaseEvent(button));
                    break;
                default: 
                    std::cout << "Key Event is neither PRESS or RELEASE!\n";
                    break;
            }
            });

    //mouse scroll events
    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) { 
            //std::cout << "MOUSE SCROLL EVENT: " << xoffset << "x" << yoffset << std::endl;
            Window* usrWindow = (Window*)glfwGetWindowUserPointer(window);
            usrWindow->EventCallback(MouseScrollEvent(xoffset, yoffset));
            });
};

void cbx::Window::Run()
{
    m_Running = true;

    cm::vec<float, 2> vecs[] = { 
        { -0.5f,  0.5f },
        {  0.5f,  0.5f },
        {  0.5f, -0.5f },
        { -0.5f, -0.5f }
    };

    cm::vec<unsigned int, 2> inds[] = {
        { 0, 1 },
        { 1, 2 },
        { 2, 3 },
        { 3, 0 }
    };
    
    ResourceManager rm("/Users/enrique/dev/climbex/res");

    Shader vertexShader(rm.ReadFile("Vertex1.shader").c_str(), Shader::Type::VERTEX);
    Shader fragmentShader1(rm.ReadFile("Fragment2.shader").c_str(), Shader::Type::FRAGMENT);

    auto program1 = std::make_unique<Program>(std::initializer_list<Shader>({vertexShader, fragmentShader1}));
    auto vao1 = std::make_unique<VertexArray>();
    auto ebo1 = std::make_unique<VertexBuffer>(sizeof(inds), inds, GL_ELEMENT_ARRAY_BUFFER);

    vao1->SetAttribute<float>(2);
    VertexBuffer vbo(sizeof(vecs), vecs, GL_ARRAY_BUFFER);
    vao1->BindBuffer(vbo);

    m_Objs = std::array<std::unique_ptr<RenderObject>, 3> { 
        std::move(program1), 
        std::move(vao1), 
        std::move(ebo1) 
    };


    while (m_Running) 
    { 
        OnUpdate();
    }
};

void cbx::Window::OnUpdate()
{
    glClearColor(cos(2 * glfwGetTime()) / 2.0f + 0.1f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Objs[0]->Bind();
    m_Objs[1]->Bind();
    m_Objs[2]->Bind();

    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

    m_Objs[0]->Unbind();
    m_Objs[1]->Unbind();
    m_Objs[2]->Unbind();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
};

void cbx::Window::OnEvent(const Event& e)
{
    Event::Dispatch<KeyPressEvent>(e, [](const KeyPressEvent& e) -> bool { 
            return false;
            });
};


