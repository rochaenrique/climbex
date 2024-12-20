#pragma once

#include "Event.h"
#include <format>

namespace cbx { 
    class KeyPressEvent : public Event 
    { 
        public: 
            KeyPressEvent(int key, int code) 
                : m_Key(key), m_Code(code) 
            {}

            inline const std::string GetString() const override 
            { 
                return std::format("KeyPressEvent: Key {}, Code {}", m_Key, m_Code); 
            };

            EVENT_TYPE(KEY_RELEASE);

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

            inline const std::string GetString() const override 
            { 
                return std::format("KeyReleaseEvent: Key {}, Code {}", m_Key, m_Code); 
            };

            EVENT_TYPE(KEY_RELEASE);

            inline int GetKey() const { return m_Key; }
            inline int GetCode() const { return m_Code; }

        private: 
            int m_Key;
            int m_Code;
    };
}
