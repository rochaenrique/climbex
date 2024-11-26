#pragma once

#include "Event.h"
#include <format>

namespace cbx { 
    class WindowResizeEvent : public Event 
    {
        public:
            WindowResizeEvent(int width, int height) 
                : m_Width(width), m_Height(height) 
            {};

            inline const std::string GetString() const override 
            {
                return std::format("WindowResizeEvent: {} x {}", m_Width, m_Height);
            };

            EVENT_TYPE(WINDOW_RESIZE);

            inline int GetWidth() const { return m_Width; };
            inline int GetHeight() const { return m_Height; };

        private:
            int m_Width;
            int m_Height;

    };
}
