#include "Axiom/Runtime/RuntimeSession.hpp"

namespace Axiom {

    void RuntimeSession::play()
    {
        m_Mode = EngineMode::Play;
    }

    void RuntimeSession::pause()
    {
        m_Mode = EngineMode::Pause;
    }

    void RuntimeSession::stop()
    {
        m_Mode = EngineMode::Stop;
    }

    EngineMode RuntimeSession::getMode() const
    {
        return m_Mode;
    }

    bool RuntimeSession::isPlaying() const
    {
        return m_Mode == EngineMode::Play;
    }

    bool RuntimeSession::isPaused() const
    {
        return m_Mode == EngineMode::Pause;
    }

    bool RuntimeSession::isEditing() const
    {
        return m_Mode == EngineMode::Edit;
    }

    bool RuntimeSession::isStopped() const
    {
        return m_Mode == EngineMode::Stop;
    }

    void RuntimeSession::edit()
    {
        m_Mode = EngineMode::Edit;
    }

}