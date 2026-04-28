#include "Axiom/Core/LayerStack.hpp"

namespace Axiom {

    void LayerStack::pushLayer(Layer* layer)
    {
        m_Layers.push_back(layer);
        layer->onAttach();
    }

    void LayerStack::popLayer(Layer* layer)
    {
        for (auto it = m_Layers.begin(); it != m_Layers.end(); ++it)
        {
            if (*it == layer)
            {
                layer->onDetach();
                m_Layers.erase(it);
                break;
            }
        }
    }

    void LayerStack::onUpdate(float dt)
    {
        for (Layer* layer : m_Layers)
            layer->onUpdate(dt);
    }

    void LayerStack::onRender()
    {
        for (Layer* layer : m_Layers)
            layer->onRender();
    }
}