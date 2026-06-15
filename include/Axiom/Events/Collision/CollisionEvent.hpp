#pragma once

#include "Axiom/Events/Event.hpp"

namespace Axiom {

    class CollisionEnterEvent : public Event
    {
    public:
        EventType getEventType() const override
        {
            return EventType::CollisionEnter;
        }

        const char* getName() const override
        {
            return "CollisionEnter";
        }
    };

    class CollisionStayEvent : public Event
    {
    public:
        EventType getEventType() const override
        {
            return EventType::CollisionStay;
        }

        const char* getName() const override
        {
            return "CollisionStay";
        }
    };

    class CollisionExitEvent : public Event
    {
    public:
        EventType getEventType() const override
        {
            return EventType::CollisionExit;
        }

        const char* getName() const override
        {
            return "CollisionExit";
        }
    };

}