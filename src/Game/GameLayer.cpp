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
#include "Axiom/Core/Application.hpp"
#include "Axiom/Core/EngineMode.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include <algorithm>

namespace Axiom {

GameLayer::GameLayer(Application* application)
    : m_Application(application)
{

    playerTex = ResourceManager::getTexture("player");

    testTex = ResourceManager::getTexture("test");

    gameplayScene = std::make_shared<Scene>();
    menuScene = std::make_shared<Scene>();

    editorScene = gameplayScene;
    runtimeScene = nullptr;

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

    editorScenes.push_back({ "Gameplay", gameplayScene });

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

    static std::string makeSceneSaveFileName(const std::string& sceneName)
    {
        std::string fileName = sceneName;

        for (char& c : fileName)
        {
            if (c == ' ')
                c = '_';
        }

        return fileName + ".scene";
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

    debugOverlay.update(dt);

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

    handleSceneSerialization();

    handleRuntimeControls();

    handleEditorTools();

    updateInspectorInfo();

    updateEditorStatus(dt);

    updateGameplay(dt);

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

void GameLayer::refreshSceneReferences()
{
    if (!scene)
    {
        player = nullptr;
        test = nullptr;
        return;
    }

    player = scene->findEntityByName("Player");
    test = scene->findEntityByName("Test");

    editorContext.clearSelection();

    if (player)
    {
        editorContext.setSelectedEntity(player);
    }
}

void GameLayer::handleRuntimeControls()
{
    if (editorUI.isPlayRequested())
    {
        if (m_Application->getMode() == EngineMode::Edit ||
            m_Application->getMode() == EngineMode::Stop)
        {            
            startRuntime();
        }

        m_Application->play();
        gameState = GameState::Gameplay;

        editorUI.resetPlayRequest();
    }

    if (editorUI.isPauseRequested())
    {
        m_Application->pause();
        gameState = GameState::Pause;
        editorUI.resetPauseRequest();
    }

    if (editorUI.isStopRequested())
    {
        m_Application->stop();

        stopRuntime();

        m_Application->setMode(EngineMode::Edit);

        gameState = GameState::Gameplay;

        editorUI.resetStopRequest();
        return;
    }
}

void GameLayer::startRuntime()
{
    runtimeScene = editorScene->clone();

    enterRuntime();
}

void GameLayer::stopRuntime()
{
    runtimeScene = nullptr;

    enterEditor();
}

void GameLayer::handleSceneSerialization()
{
    if (sceneEditorPanel.isSaveSceneRequested() ||
        editorUI.isSaveSceneRequested())
    {
        SceneSerializer::save(
            *scene,
            Paths::getSave(
                makeSceneSaveFileName(
                    sceneManager.getActiveSceneName()
                )
            )
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
            Paths::getSave(
                makeSceneSaveFileName(
                    sceneManager.getActiveSceneName()
                )
            )
        );

        refreshSceneReferences();

        sceneEditorPanel.resetLoadSceneRequest();
        editorUI.resetLoadSceneRequest();

        consolePanel.addLog("[INFO] Scene loaded");
    }
}

void GameLayer::handleEditorTools()
{
    hierarchyPanel.setEditorContext(&editorContext);
    inspectorPanel.setEditorContext(&editorContext);
    sceneEditorPanel.setEditorContext(&editorContext);
    assetBrowserPanel.setEditorContext(&editorContext);

    sceneEditorPanel.setSceneInfo(
        sceneManager.getActiveSceneName(),
        static_cast<int>(scene->getEntityCount())
    );

    sceneEditorPanel.clearSceneNames();

    for (const auto& sceneInfo : editorScenes)
    {
        sceneEditorPanel.addSceneName(sceneInfo.first);
    }

    if (sceneEditorPanel.isRenameSceneRequested())
    {
        sceneManager.renameActiveScene(
            sceneEditorPanel.getRequestedSceneName()
        );

        sceneEditorPanel.resetRenameSceneRequest();
    }

    sceneEditorPanel.setSceneMode("Edit");

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

    if (sceneEditorPanel.isNewSceneRequested())
    {
        auto newScene = std::make_shared<Scene>();

        std::string name =
            "New Scene " + std::to_string(editorScenes.size() + 1);

        editorScenes.push_back({ name, newScene });

        setActiveScene(name, newScene);

        editorContext.clearSelection();

        sceneEditorPanel.resetNewSceneRequest();
    }

    if (sceneEditorPanel.isSwitchSceneRequested())
    {
        const std::string& name =
            sceneEditorPanel.getRequestedSceneSwitchName();

        for (const auto& sceneInfo : editorScenes)
        {
            if (sceneInfo.first == name)
            {
                setActiveScene(sceneInfo.first, sceneInfo.second);
                break;
            }
        }

        sceneEditorPanel.resetSwitchSceneRequest();
    }

    if (sceneEditorPanel.isDeleteSceneRequested())
    {
        if (editorScenes.size() > 1)
        {
            const std::string activeName =
                sceneManager.getActiveSceneName();

            editorScenes.erase(
                std::remove_if(
                    editorScenes.begin(),
                    editorScenes.end(),
                    [&](const auto& sceneInfo)
                    {
                        return sceneInfo.first == activeName;
                    }
                ),
                editorScenes.end()
            );

            const auto& nextScene = editorScenes.front();

            setActiveScene(nextScene.first, nextScene.second);

            editorContext.clearSelection();
        }

        sceneEditorPanel.resetDeleteSceneRequest();
    }

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
        
        editorContext.setSelectedEntity(entity);

        sceneEditorPanel.resetCreateEntityRequest();
    }

    hierarchyPanel.clear();

    scene->forEach([&](Entity* entity)
        {
            hierarchyPanel.addEntity(entity);
        });

    if (hierarchyPanel.isCreateEntityRequested())
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

        editorContext.setSelectedEntity(entity);

        hierarchyPanel.resetCreateEntityRequest();
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

    if (Entity* source = hierarchyPanel.getDuplicateEntity())
    {
        if (!source->isDestroyed())
        {
            Entity* copy = scene->createEntity(source->getName() + " Copy");

            if (auto* sourceTransform = source->getComponent<TransformComponent>())
            {
                auto* transform = copy->addComponent<TransformComponent>();
                *transform = *sourceTransform;

                transform->position.x += 32.0f;
                transform->position.y += 32.0f;
            }

            if (auto* sourceSprite = source->getComponent<SpriteComponent>())
            {
                copy->addComponent<SpriteComponent>(
                    sourceSprite->getTextureID(),
                    sourceSprite->getTexture()
                );
            }

            editorContext.setSelectedEntity(copy);
        }

        hierarchyPanel.resetDuplicateEntityRequest();
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
}

void GameLayer::updateInspectorInfo()
{
    if (!player)
        return;

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
}

void GameLayer::updateEditorStatus(float dt)
{
    statisticsPanel.setStats(
        dt > 0.0f ? 1.0f / dt : 0.0f,
        dt,
        sceneManager.getActiveSceneName(),
        static_cast<int>(getEntityCount()),
        scene->camera.position,
        scene->camera.zoom,
        getPlayerPosition()
    );

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

    std::string stateText = "Unknown";

    if (m_Application->getMode() == EngineMode::Edit)
    {
        stateText = "Edit";
    }
    else if (m_Application->getMode() == EngineMode::Stop)
    {
        stateText = "Stop";
    }
    else if (m_Application->getMode() == EngineMode::Pause)
    {
        stateText = "Pause";
    }
    else
    {
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
    }

    debugOverlay.setGameState(stateText);

    editorUI.setStatusInfo(
        sceneManager.getActiveSceneName(),
        stateText,
        static_cast<int>(getEntityCount()),
        dt > 0.0f ? 1.0f / dt : 0.0f
    );
}

void GameLayer::updateGameplay(float dt)
{
    if (!m_Application->isPlaying())
    {
        return;
    }

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
            enterMenu();
        }
        else
        {
            enterRuntime();
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

void GameLayer::setActiveScene(const std::string& name, std::shared_ptr<Scene> newScene)
{
    scene = newScene;

    sceneManager.setActiveScene(name, scene);

    refreshSceneReferences();
}

void GameLayer::enterEditor()
{
    setActiveScene("Gameplay", editorScene);
}

void GameLayer::enterRuntime()
{
    if (!runtimeScene)
        return;

    setActiveScene("Gameplay", runtimeScene);
}

void GameLayer::enterMenu()
{
    if (!m_Application->isPlaying())
        return;

    setActiveScene("Menu", menuScene);
}

void GameLayer::onRender()
{
    if (!scene)
        return;

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