#include "Axiom/Core/Engine.hpp"
#include "Axiom/Renderer/Renderer.hpp"

namespace Axiom {

	Engine::Engine()
	{
		m_Window = new Window(1280, 720, "Axiom");
		Renderer::init();
	}

	Engine::~Engine()
	{
		delete m_Window;
	}

	void Engine::run()
	{
		while (!m_Window->shouldClose())
		{
			Renderer::clear();

			m_Window->swapBuffers();
			m_Window->pollEvents();
		}

		}
	}