#include "Texture.h"
#include <iostream>
#include <GL/glew.h>

cbx::Texture::Texture(const Image img, unsigned int location)
    : m_Location(location)
{
    glGenTextures(1, &m_RendererId);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if (img.buff) 
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.x, img.y, 0, GL_RGB + img.bpp - 3, GL_UNSIGNED_BYTE, img.buff);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else 
        std::cout << "FAILED TO LOAD TEXTURE \n";
};

void cbx::Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE0 + m_Location);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);
};

void cbx::Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, m_RendererId);
};
