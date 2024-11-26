#pragma once

#include "Event.h"
#include <format>

namespace cbx { 
    class MouseMoveEvent : public Event 
    {
        public: 
            MouseMoveEvent(double xpos, double ypos) 
                : m_XPos(xpos), m_YPos(ypos)
            {};

            inline const std::string GetString() const override 
            { 
                return std::format("MouseMoveEvent: ({}) x ({})", m_XPos, m_YPos); 
            };

            EVENT_TYPE(MOUSE_MOVE);

            inline const double GetXPos() const { return m_XPos; };
            inline const double GetYPos() const { return m_YPos; };

        private: 
            double m_XPos;
            double m_YPos;
    };

    class MouseButtonPressEvent : public Event 
    {
        public: 
            MouseButtonPressEvent(int button) 
                : m_Button(button) 
            {};

            inline const std::string GetString() const override 
            { 
                return std::format("MouseButtonPressEvent: Button {}",  m_Button); 
            };
            EVENT_TYPE(MOUSE_BUTTON_PRESS);

            inline const int GetButton() const { return m_Button; };

        private: 
            int m_Button;
    };

    class MouseButtonReleaseEvent : public Event 
    {
        public: 
            MouseButtonReleaseEvent(int button) 
                : m_Button(button) 
            {};

            inline const std::string GetString() const override 
            { 
                return std::format("MouseButtonReleaseEvent: Button {}",  m_Button); 
            };
 
            EVENT_TYPE(MOUSE_BUTTON_RELEASE);

            inline const int GetButton() const { return m_Button; };

        private: 
            int m_Button;
    };

    class MouseScrollEvent : public Event 
    {
        public: 
            MouseScrollEvent(double xOffset, double yOffset) 
                : m_XOffset(xOffset), m_YOffset(yOffset) 
             {};

            inline const std::string GetString() const override 
            { 
                return std::format("MouseScrollEvent: x {}, y {}",  m_XOffset, m_YOffset); 
            };

            EVENT_TYPE(MOUSE_SCROLL);

            inline double GetXOffset() const { return m_XOffset; };
            inline double GetYOffset() const { return m_YOffset; };

        private: 
            double m_XOffset;
            double m_YOffset;
    };
}
