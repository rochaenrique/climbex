#include "Shader.h"
#include <GL/glew.h>
#include <iostream>

cbx::Shader::Shader(const char* source, cbx::Shader::Type type)
{
    std::cout << "SHADER SOURCE:\n" << source << std::endl;
    switch (type) { 
        case VERTEX: 
            m_RendererId = glCreateShader(GL_VERTEX_SHADER);
            break;
        case FRAGMENT: 
            m_RendererId = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            throw std::exception();
    }

    glShaderSource(m_RendererId, 1, &source, NULL);
    glCompileShader(m_RendererId);

    int success;
    char infoLog[512];
    glGetShaderiv(m_RendererId, GL_COMPILE_STATUS, &success);
    if (!success) { 
        glGetShaderInfoLog(m_RendererId, 512, NULL, infoLog);
        std::cout << "ERROR WHILE COMPILING SHADER: " << infoLog << std::endl;;
    }
}


cbx::Shader::~Shader()
{
    glDeleteShader(m_RendererId);
};
