#pragma once

#include <memory>
#include <string>
#include <vector>
#include <utility>

namespace Axiom {

    class Scene;

    class SceneManager
    {
    public:
        void addScene(
            const std::string& name,
            std::shared_ptr<Scene> scene
        );

        const std::vector<
            std::pair<std::string, std::shared_ptr<Scene>>
        >& getScenes() const;

        std::shared_ptr<Scene> getScene(
            const std::string& name
        ) const;

        void setActiveScene(const std::string& name, std::shared_ptr<Scene> scene);

        std::shared_ptr<Scene> getActiveScene() const;

        std::string getActiveSceneName() const;

        bool hasActiveScene() const;

        void clearActiveScene();

        bool removeScene(const std::string& name);

        void renameActiveScene(const std::string& name);

    private:
        std::vector<
            std::pair<std::string, std::shared_ptr<Scene>>
        > m_Scenes;

        std::shared_ptr<Scene> m_ActiveScene;
        std::string m_ActiveSceneName = "None";
    };

}