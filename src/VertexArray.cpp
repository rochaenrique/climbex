#include "VertexArray.h"
#include <GL/glew.h>

cbx::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererId);
}

cbx::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererId);
}

void cbx::VertexArray::Bind() const
{
    glBindVertexArray(m_RendererId);
}

void cbx::VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void cbx::VertexArray::BindBuffer(const VertexBuffer& vb) const
{
    Bind();
    vb.Bind();

    //attribute stuff
}

