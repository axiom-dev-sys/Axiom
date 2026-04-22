#pragma once
#include "Event.hpp"



namespace Axiom {

    class KeyPressedEvent : public Event
    {
    public:
        KeyPressedEvent(int keycode)
            : m_KeyCode(keycode) {
        }

        EventType getEventType() const override
        {
            return EventType::KeyPressed;
        }

        const char* getName() const override
        {
            return "KeyPressed";
        }

        int getKeyCode() const
        {
            return m_KeyCode;
        }

    private:
        int m_KeyCode;
    };

}