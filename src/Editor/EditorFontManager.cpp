#include "Axiom/Editor/EditorFontManager.hpp"

#include "Axiom/Core/Paths.hpp"

#include <imgui.h>
#include <misc/freetype/imgui_freetype.h>

namespace Axiom 
{
    EditorFontSettings EditorFontManager::s_Settings{};

    const char* EditorFontManager::getFontPath(EditorFont font)
    {
        switch (font)
        {
        case EditorFont::RobotoMedium:
            return "fonts/Roboto-Medium.ttf";
        }

        return "";
    }

    void EditorFontManager::loadFont(EditorFont font)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.Fonts->SetFontLoader(ImGuiFreeType::GetFontLoader());
        io.Fonts->FontLoaderFlags = ImGuiFreeTypeLoaderFlags_ForceAutoHint;

        io.Fonts->AddFontFromFileTTF(
            Paths::getAsset(s_Settings.path).c_str(),
            s_Settings.size,
            nullptr,
            io.Fonts->GetGlyphRangesCyrillic()
        );
    }

    void EditorFontManager::loadDefaultFont()
    {
        loadFont(EditorFont::RobotoMedium);
    }
}