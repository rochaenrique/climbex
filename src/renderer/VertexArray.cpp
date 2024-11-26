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

    int offset = 0;
    for (int i = 0; i < m_Attributes.size(); ++i) 
    { 
        const Attribute& at = m_Attributes[i]; 
        glVertexAttribPointer(i, at.count, at.glType, at.normalized, m_AttributesStride, (void*)offset);
        glEnableVertexAttribArray(i);
        offset += at.size;
    }
}

template<typename T>
void cbx::VertexArray::SetAttribute(int count, bool normalized)
{
    throw std::exception();
};


template<>
void cbx::VertexArray::SetAttribute<float>(int count, bool normalized)
{
    VertexArray::Attribute at(GL_FLOAT, sizeof(float), count, normalized);
    m_Attributes.push_back(at);
    m_AttributesStride += at.size;
};
