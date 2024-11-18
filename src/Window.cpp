#include "Window.h"
#include "VertexBuffer.h"
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
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    }; 

    const char *vsSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char *fsSource = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    Shader vertexShader(vsSource, Shader::Type::VERTEX);
    Shader fragmentShader(fsSource, Shader::Type::FRAGMENT);

    program = std::make_unique<Program>(std::initializer_list<Shader>({vertexShader, fragmentShader}));

    VertexBuffer vbo(sizeof(vertices), vertices);
    vao = std::make_unique<VertexArray>();
    vao->BindBuffer(vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (m_Running) 
    { 
        OnUpdate();
    }

    program->~Program();
};

void cbx::Window::OnUpdate()
{
    glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    program->Bind();
    vao->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao->Unbind();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
};
