#pragma once
#include "Axiom/Core/Window.hpp"

namespace Axiom {

	class Engine
	{
	public:
		Engine();
		~Engine();

		void run();

	private:
		Window* m_Window;
	};

}