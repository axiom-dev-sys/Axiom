#pragma once
#include "Event.hpp"

namespace Axiom {

    class WindowCloseEvent : public Event
    {
    public:
        EventType getEventType() const override
        {
            return EventType::WindowClose;
        }

        const char* getName() const override
        {
            return "WindowClose";
        }
    };

}