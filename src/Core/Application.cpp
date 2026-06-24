#include "Axiom/Core/Application.hpp"

namespace Axiom {

    Application::Application() {}

    Application::~Application() 
    {
        shutdown();
    }

    void Application::init() 
    {

    }

    void Application::shutdown() 
    {

    }

    void Application::update(float dt) 
    {
        m_LayerStack.onUpdate(dt);
    }

    void Application::render() 
    {
        m_LayerStack.onRender();
    }

    void Application::pushLayer(Layer* layer) 
    {
        m_LayerStack.pushLayer(layer);
    }

}