#include "Axiom/Scene/SceneManager.hpp"
#include "Axiom/Scene/Scene.hpp"

namespace Axiom {

    void SceneManager::setActiveScene(
        const std::string& name,
        std::shared_ptr<Scene> scene)
    {
        m_ActiveSceneName = name;
        m_ActiveScene = scene;
    }

    std::shared_ptr<Scene>
    SceneManager::getActiveScene() const
    {
        return m_ActiveScene;
    }

    std::string SceneManager::getActiveSceneName() const
    {
        return m_ActiveSceneName;
    }

    bool SceneManager::hasActiveScene() const
    {
        return m_ActiveScene != nullptr;
    }

    void SceneManager::clearActiveScene()
    {
        m_ActiveSceneName = "None";
        m_ActiveScene = nullptr;
    }

    void SceneManager::renameActiveScene(const std::string& name)
    {
        if (name.empty())
            return;

        m_ActiveSceneName = name;
    }

}