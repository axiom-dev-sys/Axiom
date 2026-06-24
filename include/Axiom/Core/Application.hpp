#pragma once

#include "Axiom/Core/LayerStack.hpp"

namespace Axiom {

    class Application {
    public:
        Application();
        ~Application();

        void init();
        void shutdown();

        void update(float dt);
        void render();

        void pushLayer(Layer* layer);

    private:
        LayerStack m_LayerStack;
    };

}