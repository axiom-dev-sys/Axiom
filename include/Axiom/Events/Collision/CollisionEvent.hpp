#pragma once

#include "Axiom/Events/Event.hpp"

namespace Axiom {

    class CollisionEnterEvent : public Event
    {
    public:
        static EventType getStaticType()
        {
            return EventType::CollisionEnter;
        }

        EventType getEventType() const override
        {
            return getStaticType();
        }

        const char* getName() const override
        {
            return "CollisionEnter";
        }
    };

    class CollisionStayEvent : public Event
    {
    public:
        static EventType getStaticType()
        {
            return EventType::CollisionStay;
        }

        EventType getEventType() const override
        {
            return getStaticType();
        }

        const char* getName() const override
        {
            return "CollisionStay";
        }
    };

    class CollisionExitEvent : public Event
    {
    public:
        static EventType getStaticType()
        {
            return EventType::CollisionExit;
        }
        
        EventType getEventType() const override
        {
            return getStaticType();
        }

        const char* getName() const override
        {
            return "CollisionExit";
        }
    };

}