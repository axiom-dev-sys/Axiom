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
        std::shared_ptr<Scene> createScene(
            const std::string& name
        );

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

        std::shared_ptr<Scene> removeActiveScene(
            std::string& nextSceneName
        );

        void renameActiveScene(const std::string& name);

        bool switchScene(
            const std::string& name
        );

    private:
        std::vector<
            std::pair<std::string, std::shared_ptr<Scene>>
        > m_Scenes;

        std::shared_ptr<Scene> m_ActiveScene;
        std::string m_ActiveSceneName = "None";
    };

}