#include "VertexBuffer.h"
#include <exception>

cbx::VertexBuffer::VertexBuffer(int size, const void* data, GLenum usage) 
    : m_Usage(usage)
{ 
    if (!(m_Usage != GL_ARRAY_BUFFER || m_Usage != GL_ELEMENT_ARRAY_BUFFER)) 
        throw std::exception();

    glGenBuffers(1, &m_RendererId);
    Bind();
    glBufferData(m_Usage, size, data, GL_STATIC_DRAW);
}

cbx::VertexBuffer::~VertexBuffer() 
{
    glDeleteBuffers(1, &m_RendererId);
}

void cbx::VertexBuffer::Bind() const
{ 
    glBindBuffer(m_Usage, m_RendererId);
}

void cbx::VertexBuffer::Unbind() const  
{ 
    glBindBuffer(m_Usage, 0);
}

