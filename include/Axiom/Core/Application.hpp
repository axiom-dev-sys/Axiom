#pragma once

#include <vector>
#include "Layer.hpp"

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
        std::vector<Layer*> m_Layers;
    };

}