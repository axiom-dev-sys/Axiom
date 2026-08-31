#pragma once

namespace Axiom {

    class Scene;
    class ViewportPanel;

    class EditorCameraController
    {
    public:
        void update(
            ViewportPanel& viewport,
            Scene& scene,
            float dt
        );

        void updateKeyboard(
            ViewportPanel& viewport,
            Scene& scene,
            float dt
        );

        void updatePanning(
            ViewportPanel& viewport,
            Scene& scene
        );

        void updateZoom(
            ViewportPanel& viewport,
            Scene& scene
        );

        void resetCamera(Scene& scene);

        void reset();

    private:
        bool m_Panning = false;

        double m_LastMouseX = 0.0;
        double m_LastMouseY = 0.0;
    };

}