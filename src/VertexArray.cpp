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

template<typename T>
void cbx::VertexArray::SetAttribute(const std::string& name, T value) const
{
    throw std::exception();
}

template<>
void cbx::VertexArray::SetAttribute<float>(const std::string& name, float value) const
{
}
