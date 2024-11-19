#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

cbx::ResourceManager::ResourceManager() 
{ 
}

const std::string cbx::ResourceManager::FromFile(const std::string& filePath) const 
{ 
    std::fstream file((resPath / filePath).string());

    if (!file) 
    { 
        std::cout << "ERRROR WHILE LOADING RESOURCE: " << filePath << std::endl;
    }

    std::string line;
    std::stringstream ss;

    while (std::getline(file, line))
    {
        ss << line << std::endl;
    }
    return ss.str();
};
