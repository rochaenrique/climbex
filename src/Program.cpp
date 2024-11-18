#include "Program.h"
#include <GL/glew.h>
#include <iostream>

cbx::Program::Program(std::initializer_list<cbx::Shader> initList) 
{
    m_RendererId = glCreateProgram();

    for (const Shader& sh : initList) {
        std::cout << "Attaching Shader ID: " << sh.getRendererId() << std::endl;
        glAttachShader(m_RendererId, sh.getRendererId());
    }

    glLinkProgram(m_RendererId);

    int success;
    char infoLog[512];
    glGetProgramiv(m_RendererId, GL_LINK_STATUS, &success);
    if (!success) 
    { 
        glGetProgramInfoLog(m_RendererId, 512, NULL, infoLog);
        std::cout << "ERROR WHILE LINKING SHADERS: " << infoLog << std::endl;
    }
    
    for (const Shader& sh : initList) 
        sh.~Shader();
};

cbx::Program::~Program() 
{
    glDeleteProgram(m_RendererId);
};

void cbx::Program::Bind() const 
{
    glUseProgram(m_RendererId);
};

void cbx::Program::Unbind() const 
{

};

