#pragma once

#include <memory>

namespace Axiom {

    class Scene;

    class SceneManager
    {
    public:
        void setActiveScene(std::shared_ptr<Scene> scene);

        std::shared_ptr<Scene> getActiveScene() const;

        bool hasActiveScene() const;

        void clearActiveScene();

    private:
        std::shared_ptr<Scene> m_ActiveScene;
    };

}