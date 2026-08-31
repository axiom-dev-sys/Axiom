#pragma once

namespace Axiom {

    class EditorContext;
    class ViewportPanel;
    class Scene;
    class Entity;

    class EditorInteractionSystem
    {
    public:
        void updateSelection(
            EditorContext& context,
            ViewportPanel& viewport,
            Scene& scene
        );

        void updateDragging(
            ViewportPanel& viewport,
            Scene& scene
        );

        void updateDelete(
            EditorContext& context,
            Scene& scene
        );

        void updateFocus(
            EditorContext& context,
            Scene& scene
        );

        void focusEntity(
            Entity* entity,
            Scene& scene
        );

        void beginDragging(Entity* entity);
        void stopDragging();

        bool isDragging() const;
        bool consumeDuplicateRequest();

    private:
        bool m_EntityDragging = false;
        
        Entity* m_DraggedEntity = nullptr;

        bool m_JustStartedDragging = false;
        bool m_DeleteKeyPressedLastFrame = false;
        bool m_DuplicateKeyPressedLastFrame = false;
        bool m_FocusKeyPressedLastFrame = false;
    };

}