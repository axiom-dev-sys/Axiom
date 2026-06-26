#include "Axiom/Experimental/Game/GameLayer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Core/Paths.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Scene/SceneSerializer.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp" 
#include "Axiom/Scene/Components/VelocityComponent.hpp" 
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp" 
#include "Axiom/Scene/Components/PlayerTag.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"
#include "Axiom/Input/Input.hpp"
#include <GLFW/glfw3.h>
#include <cmath>

namespace Axiom {

GameLayer::GameLayer()
{

    playerTex = ResourceManager::getTexture("player");

    testTex = ResourceManager::getTexture("test");

    gameplayScene = std::make_shared<Scene>();
    menuScene = std::make_shared<Scene>();

    scene = gameplayScene;
    sceneManager.setActiveScene("Gameplay", scene);

    test = scene->createEntity("Test");
    
    auto* testTransform = test->addComponent<TransformComponent>();    
    testTransform->position = {500.0f, 0.0f};
    testTransform->scale = {512.0f, 512.0f};
    testTransform->rotation = 0.0f;

    auto* testCollider = test->addComponent<ColliderComponent>();
    testCollider->size = {512.0f, 512.0f};
    testCollider->offset = {0.0f, 0.0f};
    testCollider->isTrigger = false;

    test->addComponent<SpriteComponent>(
        "test",
        ResourceManager::getTexture("test")
    );

    player = scene->createEntity("Player");

    auto* playerTransform = player->addComponent<TransformComponent>();
    player->addComponent<VelocityComponent>();
    player->addComponent<PlayerControllerComponent>();
    player->addComponent<PlayerTag>();
    playerTransform->position = {0.0f, 0.0f};
    playerTransform->scale = {128.0f, 128.0f};
    playerTransform->rotation = 0.0f;

    auto* playerCollider = player->addComponent<ColliderComponent>();
    playerCollider->size = {128.0f, 128.0f};
    playerCollider->offset = {0.0f, 0.0f};
    playerCollider->isTrigger = false;

    player->addComponent<SpriteComponent>(
        "player",
        ResourceManager::getTexture("player")
    );

    consolePanel.addLog("[INFO] Axiom editor started");
    consolePanel.addLog("[INFO] Gameplay scene loaded");
    consolePanel.addLog("[INFO] ResourceManager initialized");

}

    glm::vec2 GameLayer::getPlayerPosition() const
    {
        if (!player)
        return {0.0f, 0.0f};

        auto* transform = player->getComponent<TransformComponent>();

        if (!transform)
        return {0.0f, 0.0f};

        return transform->position;
    }

    size_t GameLayer::getEntityCount() const
    {
        if (!scene)
        return 0;

        return scene->getEntityCount();
    }

    bool GameLayer::isExitRequested() const
    {
        return editorUI.isExitRequested();
    }

void GameLayer::onUpdate(float dt)
{
    if (!scene)
        return;

    bool f3Pressed = Input::isKeyDown(GLFW_KEY_F3);

    if (f3Pressed && !f3PressedLastFrame)
    {
        debugOverlay.toggle();
    }

    f3PressedLastFrame = f3Pressed;

    bool f4Pressed = Input::isKeyDown(GLFW_KEY_F4);

    if (f4Pressed && !f4PressedLastFrame)
    {
        debugRenderer.toggle();
    }

    f4PressedLastFrame = f4Pressed;

    bool f5Pressed = Input::isKeyDown(GLFW_KEY_F5);

    if (f5Pressed && !f5PressedLastFrame)
    {
        inspectorPanel.toggle();
    }

    f5PressedLastFrame = f5Pressed;

    bool f6Pressed = Input::isKeyDown(GLFW_KEY_F6);

    if (f6Pressed && !f6PressedLastFrame)
    {
        hierarchyPanel.toggle();
    }

    f6PressedLastFrame = f6Pressed;

    bool f7Pressed = Input::isKeyDown(GLFW_KEY_F7);

    if (f7Pressed && !f7PressedLastFrame)
    {
        sceneEditorPanel.toggle();
    }

    f7PressedLastFrame = f7Pressed;

    bool f8Pressed = Input::isKeyDown(GLFW_KEY_F8);

    if (f8Pressed && !f8PressedLastFrame)
    {
        assetBrowserPanel.toggle();
    }

    f8PressedLastFrame = f8Pressed;

    hierarchyPanel.setEditorContext(&editorContext);

    inspectorPanel.setEditorContext(&editorContext);

    sceneEditorPanel.setEditorContext(&editorContext);

    assetBrowserPanel.setEditorContext(&editorContext);

    debugOverlay.update(dt);

    statisticsPanel.setStats(
        dt > 0.0f ? 1.0f / dt : 0.0f,
        dt,
        sceneManager.getActiveSceneName(),
        static_cast<int>(getEntityCount()),
        scene->camera.position,
        scene->camera.zoom,
        getPlayerPosition()
    );

    if (editorUI.isDebugRendererVisible())
    {
        debugRenderer.clear();

        scene->forEach([&](Entity* entity)
            {
                auto* transform = entity->getComponent<TransformComponent>();
                auto* collider = entity->getComponent<ColliderComponent>();

                if (!transform || !collider)
                    return;

                debugRenderer.drawRect(
                    transform->position
                    - collider->size * 0.5f
                    + collider->offset,
                    collider->size
                );
            });
    }

    hierarchyPanel.clear();

    scene->forEach([&](Entity* entity)
        {
            hierarchyPanel.addEntity(entity);
        });

    Entity* selectedEntity = editorContext.getSelectedEntity();

    if (selectedEntity && selectedEntity->isDestroyed())
    {
        editorContext.clearSelection();

        selectedEntity = nullptr;
    }

    if (!selectedEntity)
    {
        selectedEntity = player;
        editorContext.setSelectedEntity(player);
    }

    assetBrowserPanel.clear();

    assetBrowserPanel.addAsset("player");
    assetBrowserPanel.addAsset("test");
    assetBrowserPanel.addAsset("office");
    assetBrowserPanel.addAsset("fallback");

    if (sceneEditorPanel.isCreateEntityRequested())
    {
        Entity* entity = scene->createEntity("New Entity");

        auto* transform =
            entity->addComponent<TransformComponent>();

        transform->position = { 0.0f, 0.0f };
        transform->scale = { 128.0f, 128.0f };

        entity->addComponent<SpriteComponent>(
            "test",
            ResourceManager::getTexture("test")
        );

        sceneEditorPanel.resetCreateEntityRequest();
    }

    if (sceneEditorPanel.isDestroyEntityRequested())
    {
        Entity* selectedEntity = editorContext.getSelectedEntity();

        if (selectedEntity && !selectedEntity->isDestroyed())
        {
            selectedEntity->destroy();
            editorContext.clearSelection();
        }

        sceneEditorPanel.resetDestroyEntityRequest();
    }

    if (assetBrowserPanel.isApplyAssetRequested())
    {
        Entity* selectedEntity = editorContext.getSelectedEntity();

        if (selectedEntity && !selectedEntity->isDestroyed())
        {
            auto* sprite =
                selectedEntity->getComponent<SpriteComponent>();

            if (sprite)
            {
                const std::string& asset =
                    assetBrowserPanel.getSelectedAsset();

                sprite->setTexture(
                    asset,
                    ResourceManager::getTexture(asset)
                );
            }
        }

        assetBrowserPanel.resetApplyAssetRequest();
    }

    if (sceneEditorPanel.isSaveSceneRequested() ||
        editorUI.isSaveSceneRequested())
    {
        SceneSerializer::save(
            *scene,
            Paths::getSave("scene.txt")
        );

        sceneEditorPanel.resetSaveSceneRequest();
        editorUI.resetSaveSceneRequest();

        consolePanel.addLog("[INFO] Scene saved");
    }
    
    if (sceneEditorPanel.isLoadSceneRequested() ||
        editorUI.isLoadSceneRequested())
    {
        SceneSerializer::load(
            *scene,
            Paths::getSave("scene.txt")
        );

        player = scene->findEntityByName("Player");
        test = scene->findEntityByName("Test");

        editorContext.clearSelection();

        if (player)
            editorContext.setSelectedEntity(player);

        sceneEditorPanel.resetLoadSceneRequest();
        editorUI.resetLoadSceneRequest();

        consolePanel.addLog("[INFO] Scene loaded");
    }

    if (editorUI.isPlayRequested())
    {
        gameState = GameState::Gameplay;
        editorUI.resetPlayRequest();
    }

    if (editorUI.isPauseRequested())
    {
        gameState = GameState::Pause;
        editorUI.resetPauseRequest();
    }

    debugOverlay.setSceneInfo(
        sceneManager.getActiveSceneName(),
        getEntityCount()
    );

    debugOverlay.setPlayerPosition(
        getPlayerPosition()
    );

    debugOverlay.setCameraPosition(
        scene->camera.position
    );

    debugOverlay.setCameraZoom(
        scene->camera.zoom
    );

    inspectorPanel.setEntityName(
        player->getName()
    );

    inspectorPanel.setEntityID(
        player->getID()
    );

    inspectorPanel.setHasSprite(
        player->hasComponent<SpriteComponent>()
    );

    inspectorPanel.setHasVelocity(
        player->hasComponent<VelocityComponent>()
    );

    inspectorPanel.setHasCollider(
        player->hasComponent<ColliderComponent>()
    );

    inspectorPanel.setHasPlayerController(
        player->hasComponent<PlayerControllerComponent>()
    );

    inspectorPanel.setHasPlayerTag(
        player->hasComponent<PlayerTag>()
    );

    std::string stateText = "Unknown";

    switch (gameState)
    {
    case GameState::Gameplay:
        stateText = "Gameplay";
        break;

    case GameState::Pause:
        stateText = "Pause";
        break;

    case GameState::Win:
        stateText = "Win";
        break;

    case GameState::GameOver:
        stateText = "Game Over";
        break;
    }

    editorUI.setStatusInfo(
        sceneManager.getActiveSceneName(),
        stateText,
        static_cast<int>(getEntityCount()),
        dt > 0.0f ? 1.0f / dt : 0.0f
    );

    bool pauseKeyPressed = Input::isKeyPressed(GLFW_KEY_P);

    if (pauseKeyPressed && !pauseKeyWasPressed)
    {
        
    if (gameState == GameState::Gameplay)
    {
        gameState = GameState::Pause;
    }
    else if (gameState == GameState::Pause)
    {
        gameState = GameState::Gameplay;
    }

    }

    pauseKeyWasPressed = pauseKeyPressed;

    if (gameState == GameState::Pause)
    {
        return;
    }

    if (gameState == GameState::GameOver || gameState == GameState::Win)
    {
        return;
    }

    bool sceneSwitchKeyPressed = Input::isKeyPressed(GLFW_KEY_F1);

    if (sceneSwitchKeyPressed && !sceneSwitchKeyWasPressed)
    {

        if (sceneManager.getActiveSceneName() == "Gameplay")
        {
            scene = menuScene;
            sceneManager.setActiveScene("Menu", scene);
        }
        else
        {
            scene = gameplayScene;
            sceneManager.setActiveScene("Gameplay", scene);
        }
    }

    sceneSwitchKeyWasPressed = sceneSwitchKeyPressed;

    if (sceneManager.getActiveSceneName() == "Menu")
    {
        scene->onUpdate(dt);
        return;
    }

    handleInteractions();

    gameContext.dt = dt;

    if (gameState == GameState::Gameplay)
    {
        gameContext.nightTime += dt;

        if (gameContext.nightTime >= gameContext.nightDuration)
        {
            gameContext.win = true;
        }
            powerSystem.update(gameContext);

            enemySystem.update(gameContext);
    }

    if (gameContext.win)
    {
        gameState = GameState::Win;
        consolePanel.addLog("[INFO] YOU WIN");
        return;
    }

    if (gameContext.gameOver)
    {
        gameState = GameState::GameOver;
        consolePanel.addLog("[INFO] GAME OVER");
        return;
    }

    if (!player || player->isDestroyed())
        return;

    if (!test || test->isDestroyed())
        return;

    auto* playerTransform = player->getComponent<TransformComponent>();

    if (!playerTransform)
        return;

    glm::vec2 oldPlayerPosition = playerTransform->position;

    scene->onUpdate(dt);

    collisionSystem.update(*scene);

    auto* testTransform = test->getComponent<TransformComponent>();

    if (testTransform)
    {    
        float dx = playerTransform->position.x - testTransform->position.x;
        float dy = playerTransform->position.y - testTransform->position.y;
        
        if (std::abs(dx) < 320.0f && std::abs(dy) < 320.0f)
        {
            playerTransform->position = oldPlayerPosition;
        }
    }
          
    scene->followCamera(player, dt);

}

void GameLayer::handleInteractions()
{
    bool cameraKeyPressed = Input::isKeyPressed(GLFW_KEY_C);

    if (cameraKeyPressed && !cameraKeyWasPressed)
    {
        gameContext.cameraOn = !gameContext.cameraOn;
    }

    cameraKeyWasPressed = cameraKeyPressed;

    bool doorKeyPressed = Input::isKeyPressed(GLFW_KEY_E);

    if (doorKeyPressed && !doorKeyWasPressed)
    {
        gameContext.doorClosed = !gameContext.doorClosed;
    }

    doorKeyWasPressed = doorKeyPressed;
}

void GameLayer::onRender()
{
    scene->onRender();

    editorUI.render();

    if (editorUI.isDebugOverlayVisible())
        debugOverlay.render();

    if (editorUI.isDebugRendererVisible())
        debugRenderer.render();

    if (editorUI.isInspectorVisible())
        inspectorPanel.render();

    if (editorUI.isHierarchyVisible())
        hierarchyPanel.render();

    if (editorUI.isSceneEditorVisible())
        sceneEditorPanel.render();

    if (editorUI.isAssetBrowserVisible())
        assetBrowserPanel.render();

    if (editorUI.isConsoleVisible())
        consolePanel.render();

    if (editorUI.isStatisticsVisible())
        statisticsPanel.render();
}

}