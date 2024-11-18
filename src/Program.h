#pragma once

#include "RenderObject.h"
#include "Shader.h"
#include <initializer_list>

namespace cbx { 
    
    class Program : public RenderObject 
    {
        public: 
            Program(std::initializer_list<Shader> initList);
            ~Program();

            void Bind() const override;
            void Unbind() const override;
        private:
            unsigned int m_RendererId;
    };
        
}
