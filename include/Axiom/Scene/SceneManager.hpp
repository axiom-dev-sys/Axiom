#pragma once

#include <memory>
#include <string>

namespace Axiom {

    class Scene;

    class SceneManager
    {
    public:
        void setActiveScene(const std::string& name, std::shared_ptr<Scene> scene);

        std::shared_ptr<Scene> getActiveScene() const;

        std::string getActiveSceneName() const;

        bool hasActiveScene() const;

        void clearActiveScene();

        void renameActiveScene(const std::string& name);

    private:
        std::shared_ptr<Scene> m_ActiveScene;
        std::string m_ActiveSceneName = "None";
    };

}