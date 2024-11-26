#pragma once

namespace cbx { 

    class Shader 
    {
        public: 
            enum Type { VERTEX, FRAGMENT };

            Shader(const char* source, Type type);
            ~Shader();

            inline unsigned int getRendererId() const { 
                return m_RendererId;
            }

        private: 
            unsigned int m_RendererId;
    };
}
