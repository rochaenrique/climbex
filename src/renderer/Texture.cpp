#include "Texture.h"
#include <filesystem>
#include <iostream>
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

cbx::Texture::Texture(const std::string& filePath, unsigned int location)
    : m_Location(location)
{
    if (!std::filesystem::exists(filePath)) 
    {
        std::cout << filePath << " TEXTURE DOES NOT EXIST!\n";
        return;
    }

    glGenTextures(1, &m_RendererId);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, n;
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &n, 0);

    if (data) 
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else 
    {
        std::cout << filePath << " FAILED TO LOAD IMAGE DATA\n";
        return;
    }
    stbi_image_free(data);
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
