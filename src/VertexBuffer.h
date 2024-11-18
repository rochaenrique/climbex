#pragma once
#include "RenderObject.h"

namespace cbx { 

    class VertexBuffer : public RenderObject 
    { 
        public: 
            VertexBuffer(int size, const float* data); 
            ~VertexBuffer(); 

            void Bind() const override;
            void Unbind() const override;

            inline unsigned int getRendererId() const { 
                return m_RendererId;
            }

        private: 
            unsigned int m_RendererId;
    };
}
