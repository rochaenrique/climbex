#pragma once
#include <filesystem>

namespace cbx { 
    class ResourceManager 
    { 
        public: 
            ResourceManager();
            const std::string FromFile(const std::string& filePath) const;

        private: 
            const std::filesystem::path resPath = std::filesystem::current_path() / ".." / "res";
    };
}
