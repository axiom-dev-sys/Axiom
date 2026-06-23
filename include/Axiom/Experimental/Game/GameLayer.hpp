#pragma once

#include "Axiom/Core/Layer.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/SceneManager.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Scene/Systems/CollisionSystem.hpp"
#include "Axiom/Experimental/Game/GameState.hpp"
#include "Axiom/Experimental/Game/GameContext.hpp"
#include "Axiom/Experimental/EnemySystem.hpp"
#include "Axiom/Experimental/PowerSystem.hpp"
#include "Axiom/DebugTools/DebugOverlay.hpp"
#include "Axiom/DebugTools/DebugRenderer.hpp"
#include "Axiom/DebugTools/InspectorPanel.hpp"
#include "Axiom/DebugTools/HierarchyPanel.hpp"
#include "Axiom/DebugTools/SceneEditorPanel.hpp"

#include <memory>
#include <string>
#include <glm/glm.hpp>

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

    glm::vec2 getPlayerPosition() const;
    size_t getEntityCount() const;

private:
    void handleInteractions();
    
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Scene> gameplayScene;
    std::shared_ptr<Scene> menuScene;
    GameContext gameContext;
    PowerSystem powerSystem;
    EnemySystem enemySystem;
    SceneManager sceneManager;
    CollisionSystem collisionSystem;
    DebugOverlay debugOverlay;
    DebugRenderer debugRenderer;
    InspectorPanel inspectorPanel;
    HierarchyPanel hierarchyPanel;
    SceneEditorPanel sceneEditorPanel;
    GameState gameState = GameState::Gameplay;

    bool pauseKeyWasPressed = false;
    bool sceneSwitchKeyWasPressed = false;
    bool cameraKeyWasPressed = false;
    bool doorKeyWasPressed = false;
    bool f3PressedLastFrame = false;
    bool f4PressedLastFrame = false;
    bool f5PressedLastFrame = false;
    bool f6PressedLastFrame = false;
    bool f7PressedLastFrame = false;

    Entity* player = nullptr;
    Entity* test = nullptr;

    Axiom::Texture* playerTex = nullptr;
    Axiom::Texture* testTex = nullptr;

};

}