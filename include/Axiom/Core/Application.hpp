#pragma once

#include "Axiom/Core/LayerStack.hpp"
#include "Axiom/Core/EngineMode.hpp"

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

        void setMode(EngineMode mode);
        EngineMode getMode() const;
        bool isPlaying() const;

    private:
        LayerStack m_LayerStack;
        EngineMode m_Mode = EngineMode::Edit;
    };

}