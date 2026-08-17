#include "Axiom/Scene/SceneManager.hpp"
#include "Axiom/Scene/Scene.hpp"

#include <algorithm>

namespace Axiom {

    std::shared_ptr<Scene> SceneManager::createScene(
        const std::string& name)
    {
        if (name.empty())
            return nullptr;

        auto scene =
            std::make_shared<Scene>();

        addScene(name, scene);

        return scene;
    }

    void SceneManager::addScene(
        const std::string& name,
        std::shared_ptr<Scene> scene)
    {
        if (!scene)
            return;

        m_Scenes.push_back({ name, scene });
    }

    const std::vector<
        std::pair<std::string, std::shared_ptr<Scene>>
    >& SceneManager::getScenes() const
    {
        return m_Scenes;
    }

    std::shared_ptr<Scene> SceneManager::getScene(
        const std::string& name) const
    {
        for (const auto& sceneInfo : m_Scenes)
        {
            if (sceneInfo.first == name)
            {
                return sceneInfo.second;
            }
        }

        return nullptr;
    }

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

    bool SceneManager::removeScene(const std::string& name)
    {
        auto it = std::remove_if(
            m_Scenes.begin(),
            m_Scenes.end(),
            [&](const auto& sceneInfo)
            {
                return sceneInfo.first == name;
            }
        );

        if (it == m_Scenes.end())
        {
            return false;
        }

        m_Scenes.erase(it, m_Scenes.end());

        return true;
    }

    std::shared_ptr<Scene> SceneManager::removeActiveScene(
        std::string& nextSceneName)
    {
        nextSceneName.clear();

        if (m_Scenes.size() <= 1)
            return nullptr;

        const std::string activeName =
            m_ActiveSceneName;

        if (!removeScene(activeName))
            return nullptr;

        if (m_Scenes.empty())
        {
            clearActiveScene();
            return nullptr;
        }

        const auto& nextScene =
            m_Scenes.front();

        nextSceneName =
            nextScene.first;

        m_ActiveSceneName =
            nextScene.first;

        m_ActiveScene =
            nextScene.second;

        return m_ActiveScene;
    }

    void SceneManager::renameActiveScene(const std::string& name)
    {
        if (name.empty())
            return;

        const std::string oldName =
            m_ActiveSceneName;

        for (auto& sceneInfo : m_Scenes)
        {
            if (sceneInfo.first == oldName)
            {
                sceneInfo.first = name;
                break;
            }
        }

        m_ActiveSceneName = name;
    }

    bool SceneManager::switchScene(
        const std::string& name)
    {
        auto targetScene =
            getScene(name);

        if (!targetScene)
            return false;

        setActiveScene(
            name,
            targetScene
        );

        return true;
    }

}