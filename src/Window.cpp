#include "Window.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Program.h"
#include "ResourceManager.h"
#include "Shader.h"
#include <iostream>

cbx::Window::Window(WindowOptions opt)
    : m_Options(opt)
{
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
    }
    
    m_Running = true;
};

void cbx::Window::Run()
{
    float vertices1[] = {
        -1.0f,   1.0f, 0.0f, // top right
         1.0f,   1.0f, 0.0f, // top left
         1.0f,  -1.0f, 0.0f, // bottom right 
        -1.0f,  -1.0f, 0.0f, // bottom left 
    };

    unsigned int indices[] = {
        0, 1, 2,   // first triangle
        0, 2, 3,   // second triangle
    }; 

    float vertices2[] = {
         // postitions       // colors
         0.25f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top
         0.75f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
        -0.25f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // bottom left
    };

    ResourceManager rm;
    Shader vertexShader(rm.FromFile("Vertex1.Shader").c_str(), Shader::Type::VERTEX);
    Shader fragmentShader1(rm.FromFile("Fractal.Shader").c_str(), Shader::Type::FRAGMENT);

    auto program1 = std::make_unique<Program>(std::initializer_list<Shader>({vertexShader, fragmentShader1}));
    auto vao1 = std::make_unique<VertexArray>();
    auto ebo1 = std::make_unique<VertexBuffer>(sizeof(indices), indices, GL_ELEMENT_ARRAY_BUFFER);
    VertexBuffer vbo1(sizeof(vertices1), vertices1, GL_ARRAY_BUFFER);
    vao1->SetAttribute<float>(3, false);
    vao1->BindBuffer(vbo1);

    m_Objs = std::array<std::unique_ptr<RenderObject>, 3> { 
        std::move(program1), 
        std::move(vao1), 
        std::move(ebo1), 
    };


    while (m_Running) 
    { 
        OnUpdate();
    }
};

void cbx::Window::OnUpdate()
{
    float time = glfwGetTime();
    float value = (sin(time) / 2.0f) + 0.5f;

    glClearColor(cos(2 * time) / 2.0f + 0.1f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Objs[0]->Bind();
    m_Objs[1]->Bind();
    m_Objs[2]->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
};
