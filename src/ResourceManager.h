#pragma once
#include <filesystem>

namespace cbx { 
    struct Image 
    {
        Image(unsigned char* buff, int x, int y, int bpp);

        unsigned char* buff = nullptr;
        int x, y, bpp, glFormat;
    };

    class ResourceManager 
    { 
        public: 
            ResourceManager(const std::string& resources);

            const std::string ReadFile(const std::string& filePath) const;
            const Image ReadImage(const std::string& filePath) const;
        private: 
            const std::filesystem::path m_ResourcePath;
    };
}
