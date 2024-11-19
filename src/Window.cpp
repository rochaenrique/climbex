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
         0.0f,  0.5f, 0.0f,  // top right
         0.0f, -0.5f, 0.0f,  // bottom right
        -1.0f, -0.5f, 0.0f,  // bottom left
        -1.0f,  0.5f, 0.0f,  // top left 
    };

    float vertices2[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3,   // second triangle
    }; 

    ResourceManager rm;
    Shader vertexShader(rm.FromFile("Vertex.Shader").c_str(), Shader::Type::VERTEX);
    Shader fragmentShader1(rm.FromFile("Fragment1.Shader").c_str(), Shader::Type::FRAGMENT);

    auto program1 = std::make_unique<Program>(std::initializer_list<Shader>({vertexShader, fragmentShader1}));
    auto vao1 = std::make_unique<VertexArray>();
    auto ebo1 = std::make_unique<VertexBuffer>(sizeof(indices), indices, GL_ELEMENT_ARRAY_BUFFER);
    VertexBuffer vbo1(sizeof(vertices1), vertices1, GL_ARRAY_BUFFER);
    vao1->BindBuffer(vbo1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader fragmentShader2(rm.FromFile("Fragment2.Shader").c_str(), Shader::Type::FRAGMENT);
    auto program2 = std::make_unique<Program>(std::initializer_list<Shader>({vertexShader, fragmentShader2}));

    auto vao2 = std::make_unique<VertexArray>();
    auto ebo2 = std::make_unique<VertexBuffer>(sizeof(indices), indices, GL_ELEMENT_ARRAY_BUFFER);
    VertexBuffer vbo2(sizeof(vertices2), vertices2, GL_ARRAY_BUFFER);
    vao2->BindBuffer(vbo2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    objs = std::array<std::unique_ptr<RenderObject>, 6> { 
        std::move(program1), 
        std::move(vao1), 
        std::move(ebo1), 
        std::move(program2), 
        std::move(vao2), 
        std::move(ebo2) 
    };


    while (m_Running) 
    { 
        OnUpdate();
    }
};

void cbx::Window::OnUpdate()
{
    glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    objs[0]->Bind();
    objs[1]->Bind();
    objs[2]->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    objs[3]->Bind();
    objs[4]->Bind();
    objs[5]->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
};
