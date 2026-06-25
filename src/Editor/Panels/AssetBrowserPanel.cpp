#include "Axiom/Editor/Panels/AssetBrowserPanel.hpp"

#include <imgui.h>

namespace Axiom {

    void AssetBrowserPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Asset Browser");

        for (const auto& asset : assets)
        {
            if (ImGui::Selectable(asset.c_str(), asset == selectedAsset))
            {
                selectedAsset = asset;
            }
        }

        ImGui::Separator();

        ImGui::Text(
            "Selected: %s",
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
            ImGui::Text("Type: Texture");
        }

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

}