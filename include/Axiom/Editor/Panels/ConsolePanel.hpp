#pragma once

#include <string>

namespace Axiom {

    class ConsolePanel
    {
    public:
        void render();

        void addLog(const std::string& message);
        void clear();

        void setVisible(bool value);
        bool isVisible() const;
        void toggle();

    private:
        bool visible = true;

        bool autoScroll = true;
        bool scrollToBottom = false;

        bool showInfo = true;
        bool showWarning = true;
        bool showError = true;

        char searchBuffer[128] = {};
    };

}