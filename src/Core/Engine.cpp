#pragma warning(disable : 26812)

#include "Axiom/Core/Engine.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/Shader.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Game/GameLayer.hpp"
#include "Axiom/Input/Input.hpp"
#include "Axiom/Core/Time.hpp"

namespace Axiom {

    Engine::Engine()
    {
        m_Window = new Window(1280, 720, "Axiom");

        Shader::init();
        Renderer::init();

        Input::setWindow(m_Window->getNative());

        m_LayerStack.pushLayer(new GameLayer());

        ResourceManager::init();
    }

    Engine::~Engine()
    {
        delete m_Window;
    }

    void Engine::run()
    {
        while (!m_Window->shouldClose())
        {
            Time::update();

            Renderer::clear();

            for (Layer* layer : m_LayerStack)
                layer->onUpdate();

            m_Window->swapBuffers();
            m_Window->pollEvents();
        }
    }

}