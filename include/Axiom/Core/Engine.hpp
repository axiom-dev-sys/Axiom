#pragma once
#include "Axiom/Core/Window.hpp"
#include "Axiom/Core/LayerStack.hpp"
#include "Axiom/Events/Event.hpp"
#include "Axiom/Core/Application.hpp"

namespace Axiom {

	class GameLayer;

	class Engine
	{
	public:
		Engine();
		~Engine();
		LayerStack m_LayerStack;
		Application m_Application;

		void onEvent(Event& event);

		void run();

	private:
		Window* m_Window;
		GameLayer* m_GameLayer = nullptr;
	};

}