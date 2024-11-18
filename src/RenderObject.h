#pragma once

namespace cbx { 

    class RenderObject 
    { 
        public:
            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;
    };
}
