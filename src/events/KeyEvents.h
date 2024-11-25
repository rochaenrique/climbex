#pragma once

#include "Event.h"

namespace cbx { 
    class KeyPressEvent : public Event 
    { 
        public: 
            KeyPressEvent(int key, int code) 
                : m_Key(key), m_Code(code) 
            {}

            inline const EmittedEvent GetType() const override { return EmittedEvent::KEY_PRESS; }

            inline int GetKey() const { return m_Key; }
            inline int GetCode() const { return m_Code; }

        private: 
            int m_Key;
            int m_Code;
    };

    class KeyReleaseEvent : public Event 
    { 
        public: 
            KeyReleaseEvent(int key, int code) 
                : m_Key(key), m_Code(code) 
            {}

            inline const EmittedEvent GetType() const override { return EmittedEvent::KEY_RELEASE; }

            inline int GetKey() const { return m_Key; }
            inline int GetCode() const { return m_Code; }

        private: 
            int m_Key;
            int m_Code;
    };
}
