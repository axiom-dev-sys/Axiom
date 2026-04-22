#pragma once
#include <string>
#include "Axiom/Events/Event.hpp"



namespace Axiom {

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& event) {}

        const std::string& getName() const { return m_Name; }

    protected:
        std::string m_Name;
    };

}