#pragma once

#include <string>
#include <iostream>

namespace cbx { 
    enum class EmittedEvent
    { 
        KEY_PRESS, KEY_RELEASE, 
        MOUSE_MOVE, 
        MOUSE_BUTTON_PRESS, MOUSE_BUTTON_RELEASE, 
        MOUSE_SCROLL, 
        WINDOW_RESIZE, WINDOW_CLOSE,
        UNDEFINED
    };

#define EVENT_TYPE(type) static EmittedEvent GetStaticType() { return EmittedEvent::type; }; EmittedEvent GetType() const override { return GetStaticType(); };

    class Event
    {
        public: 
            virtual EmittedEvent GetType() const = 0;
            virtual const std::string GetString() const = 0;

            inline bool IsHandled() const { return m_Handled; };

            template<class E, typename F>
            static inline bool Dispatch(const Event& e, const F& func)
            { 
                if (E::GetStaticType() == e.GetType())
                { 
                    if (!e.IsHandled()) return func(static_cast<const E&>(e));
                    return true;
                }
                return false;
            };

        private:
            bool m_Handled = false;
    };

}

static inline std::ostream& operator<<(std::ostream& os, const cbx::Event& event) { 
    os << event.GetString();
    return os;
}
