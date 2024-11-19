#include "Window.h"
#include "VertexBuffer.h"
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
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    ResourceManager rm;
    Shader vertexShader(rm.FromFile("Vertex.Shader").c_str(), Shader::Type::VERTEX);
    Shader fragmentShader(rm.FromFile("Fragment.Shader").c_str(), Shader::Type::FRAGMENT);

    program = std::make_unique<Program>(std::initializer_list<Shader>({vertexShader, fragmentShader}));

    VertexBuffer vbo = VertexBuffer(sizeof(vertices), vertices, GL_ARRAY_BUFFER);
    vao = std::make_unique<VertexArray>();
    vao->BindBuffer(vbo);
    ebo = std::make_unique<VertexBuffer>(sizeof(indices), indices, GL_ELEMENT_ARRAY_BUFFER);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (m_Running) 
    { 
        OnUpdate();
    }
};

void cbx::Window::OnUpdate()
{
    glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    program->Bind();
    vao->Bind();
    ebo->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao->Unbind();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
};
