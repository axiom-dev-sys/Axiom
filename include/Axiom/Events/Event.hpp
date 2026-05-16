#pragma once
#include <string>

namespace Axiom {

    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        KeyPressed,
        KeyReleased
    };

    class Event
    {
    public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;

        bool handled = false;
    };

}