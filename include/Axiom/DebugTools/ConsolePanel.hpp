#pragma once

#include <string>
#include <vector>

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
        std::vector<std::string> logs;
    };

}