#pragma once

#include "Axiom/Editor/EditorContext.hpp"

#include <string>
#include <vector>

namespace Axiom {

    class AssetBrowserPanel
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        void addAsset(const std::string& name);
        void clear();

        const std::string& getSelectedAsset() const;

        bool isApplyAssetRequested() const;
        void resetApplyAssetRequest();

        void setEditorContext(EditorContext* context);

    private:
        bool visible = true;

        std::vector<std::string> assets;
        std::string selectedAsset;

        bool applyAssetRequested = false;

        EditorContext* editorContext = nullptr;
    };

}