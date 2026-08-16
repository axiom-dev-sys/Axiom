#pragma once

namespace Axiom {

    class EditorCommandController
    {
    public:
        bool consumeSaveRequest();
        bool consumeLoadRequest();

        void resetInputState();

    private:
        bool m_SaveKeyPressedLastFrame = false;
        bool m_LoadKeyPressedLastFrame = false;
    };

}