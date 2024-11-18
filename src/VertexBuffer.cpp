#include "VertexBuffer.h"
#include <GL/glew.h>

cbx::VertexBuffer::VertexBuffer(int size, const float* data) 
{ 
    glGenBuffers(1, &m_RendererId);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

cbx::VertexBuffer::~VertexBuffer() 
{
    glDeleteBuffers(1, &m_RendererId);
}

void cbx::VertexBuffer::Bind() const
{ 
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void cbx::VertexBuffer::Unbind() const  
{ 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

