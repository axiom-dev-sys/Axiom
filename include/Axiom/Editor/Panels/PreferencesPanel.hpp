#pragma once

namespace Axiom {

    class PreferencesPanel
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;
        void toggle();

    private:
        bool visible = false;

        int themeIndex = 0;
    };

}