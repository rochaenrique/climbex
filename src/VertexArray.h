#pragma once
#include "RenderObject.h"
#include "VertexBuffer.h"
#include <string>
#include <vector>

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

            struct Attribute 
            {
                Attribute(int glType, int typeSize, int count, bool normalized)
                    : glType(glType), size(typeSize * count), count(count), normalized(normalized) 
                {};

                int glType;
                int size;
                int count;
                bool normalized;
            };

            template<typename T>
            void SetAttribute(int count, bool normalized);

        private: 
            unsigned int m_RendererId;
            std::vector<Attribute> m_Attributes;
            unsigned int m_AttributesStride = 0;
    };

}
