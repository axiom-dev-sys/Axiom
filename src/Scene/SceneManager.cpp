#include "Axiom/Scene/SceneManager.hpp"
#include "Axiom/Scene/Scene.hpp"

namespace Axiom {

    void SceneManager::setActiveScene(
        std::shared_ptr<Scene> scene)
    {
        m_ActiveScene = scene;
    }

    std::shared_ptr<Scene>
    SceneManager::getActiveScene() const
    {
        return m_ActiveScene;
    }

    bool SceneManager::hasActiveScene() const
    {
        return m_ActiveScene != nullptr;
    }

    void SceneManager::clearActiveScene()
    {
        m_ActiveScene = nullptr;
    }

}