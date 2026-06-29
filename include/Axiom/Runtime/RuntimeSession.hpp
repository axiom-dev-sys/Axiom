#pragma once

#include "Axiom/Core/EngineMode.hpp"

namespace Axiom {

    class RuntimeSession
    {
    public:
        void play();
        void pause();
        void stop();

        EngineMode getMode() const;
        bool isPlaying() const;
        bool isPaused() const;
        bool isEditing() const;
        bool isStopped() const;

    private:
        EngineMode m_Mode = EngineMode::Edit;
    };

}