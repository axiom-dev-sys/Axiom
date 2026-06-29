#pragma once

#include "Axiom/Core/LayerStack.hpp"
#include "Axiom/Core/EngineMode.hpp"
#include "Axiom/Runtime/RuntimeSession.hpp"

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

        RuntimeSession& getRuntimeSession();

        void play();
        void pause();
        void stop();

    private:
        LayerStack m_LayerStack;
        RuntimeSession m_RuntimeSession;
    };

}