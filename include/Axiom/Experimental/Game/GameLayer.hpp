#pragma once

#include "Axiom/Core/Layer.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/SceneManager.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Scene/Systems/CollisionSystem.hpp"
#include "Axiom/Experimental/Game/GameState.hpp"

#include <memory>
#include <string>

namespace Axiom {

class GameLayer : public Axiom::Layer
{
public:
    GameLayer();

    void onUpdate(float dt) override;
    void onRender() override;

    GameState getGameState() const
    {
        return gameState;
    }

    std::string getActiveSceneName() const
    {
        return sceneManager.getActiveSceneName();
    }

    bool hasActiveScene() const
    {
        return sceneManager.hasActiveScene();
    }

private:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Scene> gameplayScene;
    std::shared_ptr<Scene> menuScene;
    SceneManager sceneManager;
    CollisionSystem collisionSystem;
    GameState gameState = GameState::Gameplay;

    bool pauseKeyWasPressed = false;
    bool sceneSwitchKeyWasPressed = false;

    Entity* player = nullptr;
    Entity* test = nullptr;

    Axiom::Texture* playerTex = nullptr;
    Axiom::Texture* testTex = nullptr;

};

}