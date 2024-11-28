#pragma once

#include "RenderObject.h"
#include "../ResourceManager.h"

namespace cbx { 
    class Texture : public RenderObject
    {
        public:
            Texture(const Image& img, unsigned int location = 0);
            void Bind() const;
            void Unbind() const;

            GET_RENDERER_ID;
        private: 
            unsigned int m_RendererId;
            unsigned int m_Location;
    };
}
