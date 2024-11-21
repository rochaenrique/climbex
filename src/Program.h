#pragma once

#include "RenderObject.h"
#include "Shader.h"
#include <initializer_list>
#include <string>
#include <unordered_map>

namespace cbx { 
    
    class Program : public RenderObject 
    {
        public: 
            Program(std::initializer_list<Shader> initList);
            ~Program();

            void Bind() const override;
            void Unbind() const override;

            inline unsigned int GetRendererID() const override { return m_RendererId; };

            void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
            
        private:
            unsigned int m_RendererId;
            std::unordered_map<std::string, int> m_UniformCache;

            int GetUniformLocation(const std::string& name);
    };
        
}
