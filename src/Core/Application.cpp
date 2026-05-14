#include "Axiom/Core/Application.hpp"

namespace Axiom {

    Application::Application() {}

    Application::~Application() {}

    void Application::init() {
    
    }

    void Application::shutdown() {
        for (auto layer : m_Layers)
            delete layer;

        m_Layers.clear();
    }

    void Application::update(float dt) {
        for (auto layer : m_Layers)
            layer->onUpdate(dt);
    }

    void Application::render() {
        for (auto layer : m_Layers)
            layer->onRender();
    }

    void Application::pushLayer(Layer* layer) {
        m_Layers.push_back(layer);
    }

}