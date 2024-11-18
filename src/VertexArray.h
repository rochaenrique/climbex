#pragma once
#include "RenderObject.h"
#include "VertexBuffer.h"

namespace cbx { 

    class VertexArray : public RenderObject
    {
        public: 
            VertexArray(); 
            ~VertexArray(); 
            void Bind() const override;
            void Unbind() const override;

            void BindBuffer(const VertexBuffer& vb) const;
        private: 
            unsigned int m_RendererId;
    };

}
