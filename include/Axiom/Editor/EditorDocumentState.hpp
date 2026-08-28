#pragma once

#include <string>

namespace Axiom {

    class EditorDocumentState
    {
    public:
        void setScenePath(
            const std::string& path
        );

        const std::string& getScenePath() const;

        bool hasScenePath() const;

        void markDirty();
        void markSaved();

        bool isDirty() const;

        void reset();

    private:
        std::string m_ScenePath;
        bool m_Dirty = false;
    };

}