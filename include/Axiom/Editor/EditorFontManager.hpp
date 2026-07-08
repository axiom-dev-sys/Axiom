#pragma once

#include "Axiom/Editor/EditorFontSettings.hpp"

namespace Axiom {

    enum class EditorFont
    {
        RobotoMedium
    };

    class EditorFontManager
    {
    public:
        static void loadDefaultFont();

        static void loadFont(EditorFont font);
        static const char* getFontPath(EditorFont font);

    private:
        static EditorFontSettings s_Settings;
    };

}