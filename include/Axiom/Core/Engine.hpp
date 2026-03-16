#pragma once
#include "Axiom/Core/Window.hpp"
#include "Axiom/Core/LayerStack.hpp"
#include "Axiom/Events/Event.hpp"

namespace Axiom {

	class Engine
	{
	public:
		Engine();
		~Engine();
		LayerStack m_LayerStack;

		void onEvent(Event& event);

		void run();

	private:
		Window* m_Window;
	};

}