#pragma once

namespace Axiom {

    class EditorContext;
    class Scene;

    class EditorTransformController
    {
    public:
        void update(
            EditorContext& context,
            Scene& scene,
            float dt
        );

        void updateSnapToggle();

        void setSnapEnabled(bool enabled);
        bool isSnapEnabled() const;

        void toggleSnap();

        void setGridSize(float size);
        float getGridSize() const;

        void updateGridToggle();

        void setGridVisible(bool visible);
        bool isGridVisible() const;

        void toggleGrid();

        void resetInputState();

    private:
        bool m_SnapEnabled = true;
        float m_GridSize = 64.0f;

        bool m_GridVisible = true;
        bool m_GridKeyPressedLastFrame = false;

        bool m_SnapKeyPressedLastFrame = false;

        bool m_LeftArrowPressedLastFrame = false;
        bool m_RightArrowPressedLastFrame = false;
        bool m_UpArrowPressedLastFrame = false;
        bool m_DownArrowPressedLastFrame = false;
    };

}