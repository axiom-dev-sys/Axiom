#pragma once

#include "Axiom/Events/Event.hpp"

namespace Axiom {

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {
        }

        template<typename T, typename Func>
        bool dispatch(Func func)
        {
            if (m_Event.getEventType() == T::getStaticType())
            {
                m_Event.handled = func(static_cast<T&>(m_Event));
                return true;
            }

            return false;
        }

    private:
        Event& m_Event;
    };

}