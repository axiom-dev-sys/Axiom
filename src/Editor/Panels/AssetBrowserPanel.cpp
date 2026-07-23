#include "Axiom/Editor/Panels/AssetBrowserPanel.hpp"
#include "Axiom/Resource/AssetRegistry.hpp"

#include <imgui.h>

namespace Axiom {

    void AssetBrowserPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Asset Browser");

        ImGui::Text("Assets");
        ImGui::Text("Count: %d", AssetRegistry::getRegisteredTextureCount());

        ImGui::Separator();

        ImGui::Text(
            "Selected: %s",
            selectedAsset.empty() ? "None" : selectedAsset.c_str()
        );

        ImGui::Separator();

        ImGui::InputText(
            "Search",
            searchBuffer,
            sizeof(searchBuffer)
        );

        ImGui::Separator();

        const auto textureIDs =
            AssetRegistry::getRegisteredTextureIDs();

        if (ImGui::CollapsingHeader("Textures", ImGuiTreeNodeFlags_DefaultOpen))
        {
            for (const std::string& textureID : textureIDs)
            {
                const bool selected =
                    selectedAsset == textureID;

                if (ImGui::Selectable(textureID.c_str(), selected))
                {
                    selectedAsset = textureID;
                }
            }
        }

        if (ImGui::CollapsingHeader("Fonts"))
        {
            ImGui::TextDisabled("No fonts registered");
        }

        if (ImGui::CollapsingHeader("Audio"))
        {
            ImGui::TextDisabled("No audio assets");
        }

        ImGui::Separator();

        ImGui::Text("Selected Asset");
        ImGui::Text(
            "Name: %s",
            selectedAsset.empty() ? "None" : selectedAsset.c_str()
        );

        ImGui::Separator();
        ImGui::Text("Preview");

        if (selectedAsset.empty())
        {
            ImGui::Text("No asset selected");
        }
        else
        {
            ImGui::Text("Name: %s", selectedAsset.c_str());
            ImGui::Text("Type: %s", getAssetType(selectedAsset).c_str());
        }

        ImGui::Text(
            "Loaded: %s",
            isAssetLoaded(selectedAsset)
            ? "Yes"
            : "No"
        );

        if (!selectedAsset.empty())
        {
            if (ImGui::Button("Apply to Selected Entity"))
            {
                applyAssetRequested = true;
            }
        }

        ImGui::End();
    }

    void AssetBrowserPanel::setVisible(bool value)
    {
        visible = value;
    }

    bool AssetBrowserPanel::isVisible() const
    {
        return visible;
    }

    void AssetBrowserPanel::toggle()
    {
        visible = !visible;
    }

    void AssetBrowserPanel::addAsset(const std::string& name)
    {
        assets.push_back(name);
    }

    void AssetBrowserPanel::clear()
    {
        assets.clear();
    }

    const std::string& AssetBrowserPanel::getSelectedAsset() const
    {
        return selectedAsset;
    }

    bool AssetBrowserPanel::isApplyAssetRequested() const
    {
        return applyAssetRequested;
    }

    void AssetBrowserPanel::resetApplyAssetRequest()
    {
        applyAssetRequested = false;
    }

    void AssetBrowserPanel::setEditorContext(EditorContext* context)
    {
        editorContext = context;
    }

    std::string AssetBrowserPanel::getAssetType(const std::string& name) const
    {
        return "Texture";
    }

    bool AssetBrowserPanel::isAssetLoaded(const std::string& name) const
    {
        return !name.empty();
    }

}