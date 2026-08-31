#pragma once

#include "Axiom/Editor/EditorContext.hpp"

#include <string>

namespace Axiom {

    class AssetBrowserPanel
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        const std::string& getSelectedAsset() const;

        void setEditorContext(EditorContext* context);

        std::string getAssetType(const std::string& name) const;

        bool isAssetLoaded(const std::string& name) const;

        bool isApplyAssetRequested() const;
        void resetApplyAssetRequest();

    private:
        bool visible = true;

        std::string selectedAsset;

        bool applyAssetRequested = false;

        char searchBuffer[128] = {};

        EditorContext* editorContext = nullptr;
    };

}