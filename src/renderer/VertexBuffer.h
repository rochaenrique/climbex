#pragma once
#include "RenderObject.h"
#include <GL/glew.h>

namespace cbx { 

    class VertexBuffer : public RenderObject 
    { 
        public: 
            VertexBuffer(int size, const void* data, GLenum usage); 
            ~VertexBuffer(); 

            void Bind() const override;
            void Unbind() const override;

            inline unsigned int GetRendererID() const override { return m_RendererId; }

        private: 
            unsigned int m_RendererId;
            unsigned int m_Usage;
    };
}
