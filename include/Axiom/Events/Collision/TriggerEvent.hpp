#pragma once

#include "Axiom/Events/Event.hpp"

namespace Axiom {

    class TriggerEnterEvent : public Event
    {
    public:
        static EventType getStaticType()
        {
            return EventType::TriggerEnter;
        }

        EventType getEventType() const override
        {
            return getStaticType();
        }

        const char* getName() const override
        {
            return "TriggerEnter";
        }
    };

    class TriggerStayEvent : public Event
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
            return "TriggerStay";
        }
    };

    class TriggerExitEvent : public Event
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
            return "TriggerExit";
        }
    };

}