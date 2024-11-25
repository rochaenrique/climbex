#pragma once

#include <string>

namespace cbx { 
    enum class EmittedEvent
    { 
        KEY_PRESS, KEY_RELEASE, 
        MOUSE_MOVE, 
        MOUSE_BUTTON_PRESS, MOUSE_BUTTON_RELEASE, 
        MOUSE_SCROLL, 
        WINDOW_RESIZE, WINDOW_CLOSE
    };

    class Event
    {
        public: 
            virtual const EmittedEvent GetType() const = 0;
            virtual const std::string GetString() const = 0;
        private:
            bool m_Handled = false;
    };

}

static inline  std::ostream& operator<<(std::ostream& os, const cbx::Event& event) { 
    os << event.GetString();
    return os;
}
