#include "Axiom/Editor/Panels/AssetBrowserPanel.hpp"
#include "Axiom/Resource/AssetRegistry.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Scene.hpp"

#include <algorithm>
#include <cctype>
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
                if (searchBuffer[0] != '\0')
                {
                    std::string textureName = textureID;
                    std::string searchText = searchBuffer;

                    std::transform(
                        textureName.begin(),
                        textureName.end(),
                        textureName.begin(),
                        [](unsigned char c)
                        {
                            return static_cast<char>(std::tolower(c));
                        }
                    );

                    std::transform(
                        searchText.begin(),
                        searchText.end(),
                        searchText.begin(),
                        [](unsigned char c)
                        {
                            return static_cast<char>(std::tolower(c));
                        }
                    );

                    if (textureName.find(searchText) ==
                        std::string::npos)
                    {
                        continue;
                    }
                }

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

        if (selectedAsset.empty())
        {
            ImGui::Text("Registered: No");
            ImGui::Text("Loaded: No");
        }
        else
        {
            ImGui::Text(
                "Registered: %s",
                AssetRegistry::isTextureRegistered(selectedAsset)
                ? "Yes"
                : "No"
            );

            ImGui::Text(
                "Loaded: %s",
                isAssetLoaded(selectedAsset)
                ? "Yes"
                : "No"
            );
        }

        if (!selectedAsset.empty())
        {
            Entity* selectedEntity =
                editorContext
                ? editorContext->getSelectedEntity()
                : nullptr;

            Scene* scene =
                editorContext
                ? editorContext->getScene()
                : nullptr;

            const bool canApply =
                selectedEntity &&
                scene &&
                scene->containsEntity(selectedEntity) &&
                !selectedEntity->isDestroyed() &&
                selectedEntity->hasComponent<SpriteComponent>();

            if (!canApply)
            {
                ImGui::BeginDisabled();
            }

            if (ImGui::Button("Apply to Selected Entity"))
            {
                applyAssetRequested = true;
            }

            if (!canApply)
            {
                ImGui::EndDisabled();
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

    const std::string& AssetBrowserPanel::getSelectedAsset() const
    {
        return selectedAsset;
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
        if (name.empty())
            return false;

        return ResourceManager::isTextureLoaded(name);
    }

    bool AssetBrowserPanel::isApplyAssetRequested() const
    {
        return applyAssetRequested;
    }

    void AssetBrowserPanel::resetApplyAssetRequest()
    {
        applyAssetRequested = false;
    }

}