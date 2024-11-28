#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <format>
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

cbx::Image::Image(unsigned char* buff, int x, int y, int bpp)
    : buff(buff), x(x), y(y), bpp(bpp)
{};

cbx::ResourceManager::ResourceManager(const std::string& resources) 
    : m_ResourcePath(resources)
{ 
    if (!std::filesystem::is_directory(resources))
        std::cout << "FAILED TO LOAD RESOURCES: path '"  << resources << "'\n";
}

const std::string cbx::ResourceManager::ReadFile(const std::string& filePath) const 
{ 
    if (!std::filesystem::exists(m_ResourcePath / filePath))
        std::cout << "FILE DOES NOT EXIST '" << filePath << "'\n";

    std::cout << "LOADING RESOURCE: " << filePath << std::endl;
    std::ifstream fileStream;
    std::stringstream ss;
    try { 
        fileStream.open(m_ResourcePath / filePath);
        ss << fileStream.rdbuf();
        fileStream.close();
    } catch (const std::ifstream::failure& e)
    {
        std::cout << "ERRROR WHILE LOADING RESOURCE '" << filePath << "': " << e.what();
    }

    return ss.str();
};

const cbx::Image cbx::ResourceManager::ReadImage(const std::string& filePath) const
{
    std::string fullPath = m_ResourcePath / filePath;
    if (!std::filesystem::exists(fullPath))
        std::cout << "IMAGE DOES NOT EXIST '" << filePath << "'\n";

    std::cout << "LOADING RESOURCE: " << filePath << std::endl;

    stbi_set_flip_vertically_on_load(true);
    int width, height, bpp;
    unsigned char *data = stbi_load(fullPath.c_str(), &width, &height, &bpp, 0);

    return { data, width, height, bpp };
};
