#pragma once

#include "Axiom/Events/Event.hpp"

namespace Axiom {

    class TriggerEnterEvent : public Event
    {
    public:
        EventType getEventType() const override
        {
            return EventType::TriggerEnter;
        }

        const char* getName() const override
        {
            return "TriggerEnter";
        }
    };

    class TriggerStayEvent : public Event
    {
    public:
        EventType getEventType() const override
        {
            return EventType::TriggerStay;
        }

        const char* getName() const override
        {
            return "TriggerStay";
        }
    };

    class TriggerExitEvent : public Event
    {
    public:
        EventType getEventType() const override
        {
            return EventType::TriggerExit;
        }

        const char* getName() const override
        {
            return "TriggerExit";
        }
    };

}