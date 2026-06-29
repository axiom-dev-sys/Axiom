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

    void Application::setMode(EngineMode mode)
    {
        if (mode == EngineMode::Play)
            m_RuntimeSession.play();
        else if (mode == EngineMode::Pause)
            m_RuntimeSession.pause();
        else
            m_RuntimeSession.stop();
    }

    EngineMode Application::getMode() const
    {
        return m_RuntimeSession.getMode();
    }

    bool Application::isPlaying() const
    {
        return m_RuntimeSession.isPlaying();
    }

    RuntimeSession& Application::getRuntimeSession()
    {
        return m_RuntimeSession;
    }

    void Application::play()
    {
        m_RuntimeSession.play();
    }

    void Application::pause()
    {
        m_RuntimeSession.pause();
    }

    void Application::stop()
    {
        m_RuntimeSession.stop();
    }

}