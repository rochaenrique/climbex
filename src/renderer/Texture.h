#pragma once

#include "RenderObject.h"

#include <string>

namespace cbx { 
    class Texture : public RenderObject
    {
        public:
            Texture(const std::string& path, unsigned int location = 0);
            void Bind() const;
            void Unbind() const;

            GET_RENDERER_ID;
        private: 
            unsigned int m_RendererId;
            unsigned int m_Location;
    };
}
