#include "Axiom/Editor/EditorCommandController.hpp"

#include "Axiom/Input/Input.hpp"

#include <GLFW/glfw3.h>

namespace Axiom {

    bool EditorCommandController::consumeSaveRequest()
    {
        const bool ctrlPressed =
            Input::isKeyDown(GLFW_KEY_LEFT_CONTROL) ||
            Input::isKeyDown(GLFW_KEY_RIGHT_CONTROL);

        const bool saveKeyPressed =
            Input::isKeyDown(GLFW_KEY_S);

        const bool shortcutPressed =
            ctrlPressed &&
            saveKeyPressed;

        const bool requested =
            shortcutPressed &&
            !m_SaveKeyPressedLastFrame;

        m_SaveKeyPressedLastFrame =
            shortcutPressed;

        return requested;
    }

    bool EditorCommandController::consumeLoadRequest()
    {
        const bool ctrlPressed =
            Input::isKeyDown(GLFW_KEY_LEFT_CONTROL) ||
            Input::isKeyDown(GLFW_KEY_RIGHT_CONTROL);

        const bool loadKeyPressed =
            Input::isKeyDown(GLFW_KEY_O);

        const bool shortcutPressed =
            ctrlPressed &&
            loadKeyPressed;

        const bool requested =
            shortcutPressed &&
            !m_LoadKeyPressedLastFrame;

        m_LoadKeyPressedLastFrame =
            shortcutPressed;

        return requested;
    }

    void EditorCommandController::resetInputState()
    {
        m_SaveKeyPressedLastFrame = false;
        m_LoadKeyPressedLastFrame = false;
    }

}