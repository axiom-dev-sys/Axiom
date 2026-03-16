#include "Axiom/Core/Engine.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Game/GameLayer.hpp"
#include "Axiom/Input/Input.hpp"

namespace Axiom {

	Engine::Engine()
	{
		m_Window = new Window(1280, 720, "Axiom");
		Renderer::init();

		Input::setWindow(m_Window->getNative());

		m_LayerStack.pushLayer(new GameLayer());
	}

	Engine::~Engine()
	{
		delete m_Window;
	}

	void Engine::onEvent(Event& event)
	{
		for (Layer* layer : m_LayerStack)
		{
			layer->onEvent(event);

			if (event.handled)
				break;
		}
	}

	void Engine::run()
	{
		while (!m_Window->shouldClose())
		{
			for (Layer* layer : m_LayerStack)
				layer->onUpdate();

			Renderer::clear();

			m_Window->swapBuffers();
			m_Window->pollEvents();
		}

		}
	}