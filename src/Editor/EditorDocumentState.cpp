#include "Axiom/Editor/EditorDocumentState.hpp"

namespace Axiom {

    void EditorDocumentState::setScenePath(
        const std::string& path)
    {
        m_ScenePath = path;
    }

    const std::string&
        EditorDocumentState::getScenePath() const
    {
        return m_ScenePath;
    }

    bool EditorDocumentState::hasScenePath() const
    {
        return !m_ScenePath.empty();
    }

    void EditorDocumentState::markDirty()
    {
        m_Dirty = true;
    }

    void EditorDocumentState::markSaved()
    {
        m_Dirty = false;
    }

    bool EditorDocumentState::isDirty() const
    {
        return m_Dirty;
    }

    void EditorDocumentState::reset()
    {
        m_ScenePath.clear();
        m_Dirty = false;
    }

}