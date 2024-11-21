#pragma once
#include "RenderObject.h"
#include "VertexBuffer.h"
#include <string>

namespace cbx { 

    class VertexArray : public RenderObject
    {
        public: 
            VertexArray(); 
            ~VertexArray(); 
            void Bind() const override;
            void Unbind() const override;

            void BindBuffer(const VertexBuffer& vb) const;

            inline unsigned int GetRendererID() const override { return m_RendererId; };

            template<typename T>
            void SetAttribute(const std::string& name, T value) const;

        private: 
            unsigned int m_RendererId;
    };

}
