#include "Axiom/Experimental/Game/GameLayer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Resource/AssetRegistry.hpp"
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
#include <imgui.h>
#include <cmath>
#include <string>
#include <algorithm>

namespace Axiom {

GameLayer::GameLayer(Application* application)
    : m_Application(application)
{
    initializeDefaultScene();

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

    handleRuntimeControls();

    handleViewportCamera(dt);
    handleSceneEditingInput(dt);
    handleEditorShortcuts();

    debugOverlay.update(dt);

    updateDebugRenderer();
    handleSceneSerialization();
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
        if (m_Application->getMode() == EngineMode::Play ||
            m_Application->getMode() == EngineMode::Pause)
        {
            m_Application->stop();

            stopRuntime();

            m_Application->setMode(EngineMode::Edit);

            gameState = GameState::Gameplay;
        }

        editorUI.resetStopRequest();
        return;
    }
}

void GameLayer::startRuntime()
{
    resetEditorInteractionState();

    runtimeScene = editorScene->clone();

    resetGameSession();

    enterRuntime();
}

void GameLayer::stopRuntime()
{
    resetEditorInteractionState();

    editorContext.clearSelection();

    runtimeScene = nullptr;

    enterEditor();

    updateEditorPanels();
    refreshCachedEntities();
}

void GameLayer::resetGameSession()
{
    gameContext.nightTime = 0.0f;
    gameContext.power = 100.0f;

    gameContext.cameraOn = false;
    gameContext.doorClosed = false;

    gameContext.win = false;
    gameContext.gameOver = false;

    gameContext.enemyState = EnemyState::Idle;

    gameState = GameState::Gameplay;
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
    updateEditorPanels();
    handleSceneEditorRequests();
    handleHierarchyRequests();
    handleAssetBrowserRequests();
    refreshCachedEntities();

    Entity* selectedEntity = editorContext.getSelectedEntity();

    if (selectedEntity && selectedEntity->isDestroyed())
    {
        editorContext.clearSelection();
    }
}

void GameLayer::updateInspectorInfo()
{
    Entity* selectedEntity =
        editorContext.getSelectedEntity();

    if (!scene ||
        !selectedEntity ||
        !scene->containsEntity(selectedEntity))
    {
        editorContext.clearSelection();

        inspectorPanel.setHasSprite(false);
        inspectorPanel.setHasVelocity(false);
        inspectorPanel.setHasCollider(false);
        inspectorPanel.setHasPlayerController(false);
        inspectorPanel.setHasPlayerTag(false);

        return;
    }

    if (selectedEntity->isDestroyed())
    {
        inspectorPanel.setHasSprite(false);
        inspectorPanel.setHasVelocity(false);
        inspectorPanel.setHasCollider(false);
        inspectorPanel.setHasPlayerController(false);
        inspectorPanel.setHasPlayerTag(false);

        return;
    }

    inspectorPanel.setHasSprite(
        selectedEntity->hasComponent<SpriteComponent>()
    );

    inspectorPanel.setHasVelocity(
        selectedEntity->hasComponent<VelocityComponent>()
    );

    inspectorPanel.setHasCollider(
        selectedEntity->hasComponent<ColliderComponent>()
    );

    inspectorPanel.setHasPlayerController(
        selectedEntity->hasComponent<PlayerControllerComponent>()
    );

    inspectorPanel.setHasPlayerTag(
        selectedEntity->hasComponent<PlayerTag>()
    );
}

void GameLayer::updateEditorStatus(float dt)
{
    int spriteCount = 0;
    int colliderCount = 0;
    int velocityCount = 0;
    int playerControllerCount = 0;

    scene->forEach([&](Entity* entity)
        {
            if (entity->hasComponent<SpriteComponent>())
                spriteCount++;

            if (entity->hasComponent<ColliderComponent>())
                colliderCount++;

            if (entity->hasComponent<VelocityComponent>())
                velocityCount++;

            if (entity->hasComponent<PlayerControllerComponent>())
                playerControllerCount++;
        });

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
        case GameState::Menu:
            stateText = "Menu";
            break;

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

    statisticsPanel.setStats(
        dt > 0.0f ? 1.0f / dt : 0.0f,
        dt,
        sceneManager.getActiveSceneName(),
        static_cast<int>(getEntityCount()),
        scene->camera.position,
        scene->camera.zoom,
        getPlayerPosition(),
        spriteCount,
        colliderCount,
        velocityCount,
        playerControllerCount,
        AssetRegistry::getRegisteredTextureCount(),
        ResourceManager::getLoadedTextureCount(),
        stateText,
        1280,
        720
    );

    debugOverlay.setGameState(stateText);

    editorUI.setStatusInfo(
        sceneManager.getActiveSceneName(),
        stateText,
        static_cast<int>(getEntityCount()),
        dt > 0.0f ? 1.0f / dt : 0.0f,
        m_SnapEnabled
    );

    sceneEditorPanel.setSceneMode(stateText);
}

void GameLayer::handleGameplayPause()
{
    bool pauseKeyPressed =
        Input::isKeyPressed(GLFW_KEY_P);

    if (pauseKeyPressed &&
        !pauseKeyWasPressed)
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

    pauseKeyWasPressed =
        pauseKeyPressed;
}

void GameLayer::handleRuntimeSceneSwitch()
{
    bool sceneSwitchKeyPressed =
        Input::isKeyPressed(GLFW_KEY_F1);

    if (sceneSwitchKeyPressed &&
        !sceneSwitchKeyWasPressed)
    {
        if (gameState == GameState::Menu)
        {
            startGameFromMenu();
        }
        else if (gameState == GameState::Gameplay)
        {
            returnToMenu();
        }
    }

    sceneSwitchKeyWasPressed =
        sceneSwitchKeyPressed;
}

void GameLayer::updateGameSystems(float dt)
{
    if (gameState == GameState::Gameplay)
    {
        gameContext.nightTime += dt;

        if (gameContext.nightTime >=
            gameContext.nightDuration)
        {
            gameContext.win = true;
        }

        powerSystem.update(gameContext);
        enemySystem.update(gameContext);
    }
}

Entity* GameLayer::findPlayer() const
{
    if (!scene)
    {
        return nullptr;
    }

    return scene->findEntityByName("Player");
}

void GameLayer::handleGameStateTransitions()
{
    if (gameContext.win)
    {
        gameState = GameState::Win;
        consolePanel.addLog("[INFO] YOU WIN");
    }

    if (gameContext.gameOver)
    {
        gameState = GameState::GameOver;
        consolePanel.addLog("[INFO] GAME OVER");
    }
}

void GameLayer::handleGameRestart()
{
    bool restartKeyPressed =
        Input::isKeyPressed(GLFW_KEY_R);

    if (restartKeyPressed &&
        !restartKeyWasPressed)
    {
        if (gameState == GameState::Win ||
            gameState == GameState::GameOver)
        {
            stopRuntime();
            startRuntime();

            m_Application->play();
        }
    }

    restartKeyWasPressed =
        restartKeyPressed;
}

void GameLayer::renderGameStateUI()
{
    if (gameState != GameState::Win &&
        gameState != GameState::GameOver)
    {
        return;
    }

    ImGuiIO& io = ImGui::GetIO();

    ImVec2 windowSize(320.0f, 140.0f);

    ImGui::SetNextWindowSize(windowSize);

    ImGui::SetNextWindowPos(
        ImVec2(
            (io.DisplaySize.x - windowSize.x) * 0.5f,
            (io.DisplaySize.y - windowSize.y) * 0.5f
        ),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse;

    const char* windowTitle =
        gameState == GameState::Win
        ? "Victory"
        : "Game Over";

    ImGui::Begin(windowTitle, nullptr, flags);

    ImGui::Spacing();

    if (gameState == GameState::Win)
    {
        ImGui::Text("YOU WIN");
    }
    else
    {
        ImGui::Text("GAME OVER");
    }

    ImGui::Separator();

    ImGui::Spacing();
    ImGui::Text("Press R to restart");

    ImGui::End();
}

void GameLayer::renderPauseUI()
{
    if (gameState != GameState::Pause)
    {
        return;
    }

    ImGuiIO& io = ImGui::GetIO();

    ImVec2 windowSize(320.0f, 140.0f);

    ImGui::SetNextWindowSize(windowSize);

    ImGui::SetNextWindowPos(
        ImVec2(
            (io.DisplaySize.x - windowSize.x) * 0.5f,
            (io.DisplaySize.y - windowSize.y) * 0.5f
        ),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Pause", nullptr, flags);

    ImGui::Spacing();

    ImGui::Text("PAUSED");

    ImGui::Separator();

    ImGui::Spacing();

    ImGui::Text("Press P to continue");

    ImGui::Spacing();

    if (ImGui::Button("Resume"))
    {
        gameState = GameState::Gameplay;
    }

    ImGui::Spacing();

    if (ImGui::Button("Restart"))
    {
        stopRuntime();
        startRuntime();

        m_Application->play();
    }

    ImGui::Spacing();

    if (ImGui::Button("Return to Menu"))
    {
        returnToMenuFromPause();
    }

    ImGui::End();
}

void GameLayer::returnToMenuFromPause()
{
    returnToMenu();
}

void GameLayer::startGameFromMenu()
{
    resetGameSession();

    enterRuntime();

    m_Application->play();
}

void GameLayer::renderMainMenuUI()
{
    if (gameState != GameState::Menu)
    {
        return;
    }

    ImGuiIO& io = ImGui::GetIO();

    ImVec2 windowSize(320.0f, 180.0f);

    ImGui::SetNextWindowSize(
        windowSize,
        ImGuiCond_Always
    );

    ImGui::SetNextWindowPos(
        ImVec2(
            (io.DisplaySize.x - windowSize.x) * 0.5f,
            (io.DisplaySize.y - windowSize.y) * 0.5f
        ),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Main Menu", nullptr, flags);

    ImGui::Spacing();
    ImGui::Text("AXIOM GAME");

    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button(
        "Start Game",
        ImVec2(280.0f, 40.0f)
    ))
    {
        startGameFromMenu();
    }

    ImGui::Spacing();

    if (ImGui::Button(
        "Exit to Editor",
        ImVec2(280.0f, 40.0f)
    ))
    {
        exitToEditor();
    }

    ImGui::End();
}

void GameLayer::returnToMenu()
{
    gameState = GameState::Menu;

    m_Application->play();

    enterMenu();
}

void GameLayer::updateGameplay(float dt)
{
    if (!m_Application->isPlaying())
    {
        return;
    }

    handleGameplayPause();
    handleGameRestart();

    if (gameState == GameState::Pause)
    {
        return;
    }

    if (gameState == GameState::GameOver || gameState == GameState::Win)
    {
        return;
    }

    handleRuntimeSceneSwitch();

    if (sceneManager.getActiveSceneName() == "Menu")
    {
        scene->onUpdate(dt);
        return;
    }

    handleInteractions();

    gameContext.dt = dt;

    updateGameSystems(dt);

    handleGameStateTransitions();

    if (!player || player->isDestroyed())
        return;

    auto* playerTransform = player->getComponent<TransformComponent>();

    if (!playerTransform)
        return;

    glm::vec2 oldPlayerPosition = playerTransform->position;

    scene->onUpdate(dt);

    collisionSystem.update(*scene);

    if (test && !test->isDestroyed())
    {
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
    }

    scene->followCamera(player, dt);
}

void GameLayer::initializeDefaultScene()
{
    gameplayScene = std::make_shared<Scene>();
    menuScene = std::make_shared<Scene>();

    editorScene = gameplayScene;
    runtimeScene = nullptr;

    scene = gameplayScene;
    sceneManager.setActiveScene("Gameplay", scene);

    test = createTestEntity();
    player = createPlayerEntity();

    editorScenes.push_back({ "Gameplay", gameplayScene });
}

Entity* GameLayer::createDefaultEntity(
    const std::string& name
)
{
    if (!scene)
    {
        return nullptr;
    }

    Entity* entity =
        scene->createEntity(name);

    auto* transform =
        entity->addComponent<TransformComponent>();

    transform->position = { 0.0f, 0.0f };
    transform->scale = { 128.0f, 128.0f };
    transform->rotation = 0.0f;

    entity->addComponent<SpriteComponent>(
        "test",
        ResourceManager::getTexture("test")
    );

    return entity;
}

Entity* GameLayer::createTestEntity()
{
    if (!scene)
    {
        return nullptr;
    }

    Entity* entity =
        scene->createEntity("Test");

    auto* transform =
        entity->addComponent<TransformComponent>();

    transform->position = { 500.0f, 0.0f };
    transform->scale = { 512.0f, 512.0f };
    transform->rotation = 0.0f;

    auto* collider =
        entity->addComponent<ColliderComponent>();

    collider->size = { 512.0f, 512.0f };
    collider->offset = { 0.0f, 0.0f };
    collider->isTrigger = false;

    entity->addComponent<SpriteComponent>(
        "test",
        ResourceManager::getTexture("test")
    );

    return entity;
}

Entity* GameLayer::createPlayerEntity()
{
    if (!scene)
    {
        return nullptr;
    }

    Entity* entity =
        scene->createEntity("Player");

    auto* transform =
        entity->addComponent<TransformComponent>();

    transform->position = { 0.0f, 0.0f };
    transform->scale = { 128.0f, 128.0f };
    transform->rotation = 0.0f;

    entity->addComponent<VelocityComponent>();
    entity->addComponent<PlayerControllerComponent>();
    entity->addComponent<PlayerTag>();

    auto* collider =
        entity->addComponent<ColliderComponent>();

    collider->size = { 128.0f, 128.0f };
    collider->offset = { 0.0f, 0.0f };
    collider->isTrigger = false;

    entity->addComponent<SpriteComponent>(
        "player",
        ResourceManager::getTexture("player")
    );

    return entity;
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

void GameLayer::exitToEditor()
{
    stopRuntime();

    m_Application->stop();
    m_Application->setMode(EngineMode::Edit);

    gameState = GameState::Gameplay;
}

void GameLayer::resetEditorInteractionState()
{
    m_EntityDragging = false;
    m_DraggedEntity = nullptr;

    m_ViewportPanning = false;

    m_LeftArrowPressedLastFrame = false;
    m_RightArrowPressedLastFrame = false;
    m_UpArrowPressedLastFrame = false;
    m_DownArrowPressedLastFrame = false;

    m_SnapKeyPressedLastFrame = false;
    m_GridKeyPressedLastFrame = false;

    m_DeleteKeyPressedLastFrame = false;

    m_DuplicateKeyPressedLastFrame = false;

    m_FocusKeyPressedLastFrame = false;

    m_SaveKeyPressedLastFrame = false;
    m_LoadKeyPressedLastFrame = false;
}

void GameLayer::handleViewportCamera(float dt)
{
    if (!editorUI.isViewportVisible())
        return;

    const bool ctrlPressed =
        Input::isKeyDown(GLFW_KEY_LEFT_CONTROL) ||
        Input::isKeyDown(GLFW_KEY_RIGHT_CONTROL);

    if (viewportPanel.isFocused() &&
        !ctrlPressed)
    {
        const float cameraSpeed = 400.0f;

        if (Input::isKeyPressed(GLFW_KEY_W))
            scene->camera.position.y += cameraSpeed * dt;

        if (Input::isKeyPressed(GLFW_KEY_S))
            scene->camera.position.y -= cameraSpeed * dt;

        if (Input::isKeyPressed(GLFW_KEY_A))
            scene->camera.position.x -= cameraSpeed * dt;

        if (Input::isKeyPressed(GLFW_KEY_D))
            scene->camera.position.x += cameraSpeed * dt;
    }

    if (viewportPanel.isHovered())
    {
        if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
        {
            const double mouseX = Input::getMouseX();
            const double mouseY = Input::getMouseY();

            if (!m_ViewportPanning)
            {
                m_LastMouseX = mouseX;
                m_LastMouseY = mouseY;
                m_ViewportPanning = true;
            }
            else
            {
                const double deltaX =
                    mouseX - m_LastMouseX;

                const double deltaY =
                    mouseY - m_LastMouseY;

                scene->camera.position.x -=
                    static_cast<float>(deltaX) *
                    scene->camera.zoom;

                scene->camera.position.y +=
                    static_cast<float>(deltaY) *
                    scene->camera.zoom;

                m_LastMouseX = mouseX;
                m_LastMouseY = mouseY;
            }
        }
        else
        {
            m_ViewportPanning = false;
        }
    }
    else
    {
        m_ViewportPanning = false;
    }
}

void GameLayer::handleSceneEditingInput(float dt)
{
    if (m_Application->getMode() != EngineMode::Edit)
        return;

    if (ImGui::GetIO().WantTextInput)
    {
        return;
    }

    const bool snapKeyPressed =
        Input::isKeyDown(GLFW_KEY_G);

    if (snapKeyPressed &&
        !m_SnapKeyPressedLastFrame)
    {
        m_SnapEnabled = !m_SnapEnabled;
    }

    m_SnapKeyPressedLastFrame =
        snapKeyPressed;

    const bool gridKeyPressed =
        Input::isKeyDown(GLFW_KEY_H);

    if (gridKeyPressed &&
        !m_GridKeyPressedLastFrame)
    {
        m_GridVisible = !m_GridVisible;
    }

    m_GridKeyPressedLastFrame =
        gridKeyPressed;

    if (!editorUI.isViewportVisible() ||
        !viewportPanel.isFocused())
    {
        return;
    }

    const bool deleteKeyPressed =
        Input::isKeyDown(GLFW_KEY_DELETE);

    Entity* selectedEntity =
        editorContext.getSelectedEntity();

    if (deleteKeyPressed &&
        !m_DeleteKeyPressedLastFrame &&
        selectedEntity &&
        scene->containsEntity(selectedEntity) &&
        !selectedEntity->isDestroyed())
    {
        selectedEntity->destroy();

        editorContext.clearSelection();

        if (m_DraggedEntity == selectedEntity)
        {
            m_EntityDragging = false;
            m_DraggedEntity = nullptr;
        }
    }

    m_DeleteKeyPressedLastFrame =
        deleteKeyPressed;

    const bool ctrlPressed =
        Input::isKeyDown(GLFW_KEY_LEFT_CONTROL) ||
        Input::isKeyDown(GLFW_KEY_RIGHT_CONTROL);

    const bool duplicateKeyPressed =
        Input::isKeyDown(GLFW_KEY_D);

    const bool duplicateShortcutPressed =
        ctrlPressed &&
        duplicateKeyPressed;

    if (duplicateShortcutPressed &&
        !m_DuplicateKeyPressedLastFrame)
    {
        Entity* selectedEntity =
            editorContext.getSelectedEntity();

        duplicateEntity(selectedEntity);
    }

    m_DuplicateKeyPressedLastFrame =
        duplicateShortcutPressed;

    const bool saveKeyPressed =
        Input::isKeyDown(GLFW_KEY_S);

    const bool saveShortcutPressed =
        ctrlPressed &&
        saveKeyPressed;

    if (saveShortcutPressed &&
        !m_SaveKeyPressedLastFrame)
    {
        editorUI.requestSaveScene();
    }

    m_SaveKeyPressedLastFrame =
        saveShortcutPressed;

    const bool loadKeyPressed =
        Input::isKeyDown(GLFW_KEY_O);

    const bool loadShortcutPressed =
        ctrlPressed &&
        loadKeyPressed;

    if (loadShortcutPressed &&
        !m_LoadKeyPressedLastFrame)
    {
        editorUI.requestLoadScene();
    }

    m_LoadKeyPressedLastFrame =
        loadShortcutPressed;

    if (!selectedEntity ||
        !scene->containsEntity(selectedEntity) ||
        selectedEntity->isDestroyed())
    {
        return;
    }

    const bool focusKeyPressed =
        Input::isKeyDown(GLFW_KEY_F);

    if (focusKeyPressed &&
        !m_FocusKeyPressedLastFrame &&
        selectedEntity &&
        scene->containsEntity(selectedEntity) &&
        !selectedEntity->isDestroyed())
    {
        auto* transform =
            selectedEntity->getComponent<TransformComponent>();

        if (transform)
        {
            scene->camera.position =
                transform->position;
        }
    }

    m_FocusKeyPressedLastFrame =
        focusKeyPressed;

    auto* transform =
        selectedEntity->getComponent<TransformComponent>();

    if (!transform ||
        m_EntityDragging)
    {
        return;
    }

    if (m_SnapEnabled)
    {
        const bool leftPressed =
            Input::isKeyDown(GLFW_KEY_LEFT);

        const bool rightPressed =
            Input::isKeyDown(GLFW_KEY_RIGHT);

        const bool upPressed =
            Input::isKeyDown(GLFW_KEY_UP);

        const bool downPressed =
            Input::isKeyDown(GLFW_KEY_DOWN);

        transform->position.x =
            std::round(
                transform->position.x /
                m_GridSize
            ) * m_GridSize;

        transform->position.y =
            std::round(
                transform->position.y /
                m_GridSize
            ) * m_GridSize;

        if (leftPressed &&
            !m_LeftArrowPressedLastFrame)
        {
            transform->position.x -= m_GridSize;
        }

        if (rightPressed &&
            !m_RightArrowPressedLastFrame)
        {
            transform->position.x += m_GridSize;
        }

        if (upPressed &&
            !m_UpArrowPressedLastFrame)
        {
            transform->position.y += m_GridSize;
        }

        if (downPressed &&
            !m_DownArrowPressedLastFrame)
        {
            transform->position.y -= m_GridSize;
        }

        m_LeftArrowPressedLastFrame = leftPressed;
        m_RightArrowPressedLastFrame = rightPressed;
        m_UpArrowPressedLastFrame = upPressed;
        m_DownArrowPressedLastFrame = downPressed;
    }
    else
    {
        m_LeftArrowPressedLastFrame = false;
        m_RightArrowPressedLastFrame = false;
        m_UpArrowPressedLastFrame = false;
        m_DownArrowPressedLastFrame = false;

        const float moveSpeed = 200.0f;

        if (Input::isKeyPressed(GLFW_KEY_LEFT))
            transform->position.x -= moveSpeed * dt;

        if (Input::isKeyPressed(GLFW_KEY_RIGHT))
            transform->position.x += moveSpeed * dt;

        if (Input::isKeyPressed(GLFW_KEY_UP))
            transform->position.y += moveSpeed * dt;

        if (Input::isKeyPressed(GLFW_KEY_DOWN))
            transform->position.y -= moveSpeed * dt;
    }
}

void GameLayer::handleViewportSelection()
{
    if (!editorUI.isViewportVisible())
        return;

    if (!viewportPanel.isLeftMouseClicked())
        return;

    const ImVec2 mousePosition =
        ImGui::GetMousePos();

    const ImVec2 boundsMin =
        viewportPanel.getBoundsMin();

    const ImVec2 viewportSize =
        viewportPanel.getSize();

    if (viewportSize.x <= 0.0f ||
        viewportSize.y <= 0.0f)
    {
        return;
    }

    const float localX =
        mousePosition.x - boundsMin.x;

    const float localY =
        mousePosition.y - boundsMin.y;

    const float normalizedX =
        localX / viewportSize.x;

    const float normalizedY =
        localY / viewportSize.y;

    const float worldX =
        scene->camera.position.x +
        (normalizedX * 2.0f - 1.0f) *
        640.0f *
        scene->camera.zoom;

    const float worldY =
        scene->camera.position.y +
        (1.0f - normalizedY * 2.0f) *
        360.0f *
        scene->camera.zoom;

    Entity* selectedEntity = nullptr;

    scene->forEach([&](Entity* entity)
    {
        auto* transform =
            entity->getComponent<TransformComponent>();

        if (!transform)
            return;

        glm::vec2 size =
            transform->scale;

        if (auto* collider =
            entity->getComponent<ColliderComponent>())
        {
            size = collider->size;
        }

        const glm::vec2 halfSize =
            size * 0.5f;

        const bool inside =
            worldX >= transform->position.x - halfSize.x &&
            worldX <= transform->position.x + halfSize.x &&
            worldY >= transform->position.y - halfSize.y &&
            worldY <= transform->position.y + halfSize.y;

        if (inside)
        {
            selectedEntity = entity;
        }
    });

    if (selectedEntity)
    {
        editorContext.setSelectedEntity(
            selectedEntity
        );

        m_EntityDragging = true;
        m_DraggedEntity = selectedEntity;
    }
    else
    {
        editorContext.clearSelection();

        m_EntityDragging = false;
        m_DraggedEntity = nullptr;
    }
}

void GameLayer::handleEntityDragging()
{
    if (!m_EntityDragging)
        return;

    const bool leftMouseDown =
        ImGui::IsMouseDown(
            ImGuiMouseButton_Left
        );

    if (!leftMouseDown)
    {
        m_EntityDragging = false;
        m_DraggedEntity = nullptr;
        return;
    }

    if (!m_DraggedEntity ||
        !scene->containsEntity(m_DraggedEntity) ||
        m_DraggedEntity->isDestroyed())
    {
        m_EntityDragging = false;
        m_DraggedEntity = nullptr;
        return;
    }

    const ImVec2 mouseDelta =
        ImGui::GetIO().MouseDelta;

    const ImVec2 viewportSize =
        viewportPanel.getSize();

    auto* transform =
        m_DraggedEntity
        ->getComponent<TransformComponent>();

    if (!transform ||
        viewportSize.x <= 0.0f ||
        viewportSize.y <= 0.0f)
    {
        return;
    }

    const float worldPerPixelX =
        1280.0f *
        scene->camera.zoom /
        viewportSize.x;

    const float worldPerPixelY =
        720.0f *
        scene->camera.zoom /
        viewportSize.y;

    transform->position.x +=
        mouseDelta.x *
        worldPerPixelX;

    transform->position.y -=
        mouseDelta.y *
        worldPerPixelY;
}

void GameLayer::handleViewportZoom()
{
    if (!editorUI.isViewportVisible() ||
        !viewportPanel.isHovered())
    {
        return;
    }
    
    const float wheel =
        ImGui::GetIO().MouseWheel;
    
    if (wheel != 0.0f)
    {
        scene->camera.zoom -= wheel * 0.1f;
        
        scene->camera.zoom = std::clamp(
            scene->camera.zoom,
            0.1f,
            5.0f
        );
    }
}

void GameLayer::handleEditorShortcuts()
{
    bool f3Pressed =
        Input::isKeyDown(GLFW_KEY_F3);

    if (f3Pressed &&
        !f3PressedLastFrame)
    {
        debugOverlay.toggle();
    }

    f3PressedLastFrame =
        f3Pressed;


    bool f4Pressed =
        Input::isKeyDown(GLFW_KEY_F4);

    if (f4Pressed &&
        !f4PressedLastFrame)
    {
        debugRenderer.toggle();
    }

    f4PressedLastFrame =
        f4Pressed;


    bool f5Pressed =
        Input::isKeyDown(GLFW_KEY_F5);

    if (f5Pressed &&
        !f5PressedLastFrame)
    {
        inspectorPanel.toggle();
    }

    f5PressedLastFrame =
        f5Pressed;


    bool f6Pressed =
        Input::isKeyDown(GLFW_KEY_F6);

    if (f6Pressed &&
        !f6PressedLastFrame)
    {
        hierarchyPanel.toggle();
    }

    f6PressedLastFrame =
        f6Pressed;


    bool f7Pressed =
        Input::isKeyDown(GLFW_KEY_F7);

    if (f7Pressed &&
        !f7PressedLastFrame)
    {
        sceneEditorPanel.toggle();
    }

    f7PressedLastFrame =
        f7Pressed;


    bool f8Pressed =
        Input::isKeyDown(GLFW_KEY_F8);

    if (f8Pressed &&
        !f8PressedLastFrame)
    {
        assetBrowserPanel.toggle();
    }

    f8PressedLastFrame =
        f8Pressed;
}

void GameLayer::updateDebugRenderer()
{
    debugRenderer.clear();

    if (!editorUI.isDebugRendererVisible())
        return;

    if (m_GridVisible)
    {
        const float m_GridSize = 64.0f;
        const float m_GridExtent = 2048.0f;

        for (float x = -m_GridExtent; x <= m_GridExtent; x += m_GridSize)
        {
            debugRenderer.drawLine(
                { x, -m_GridExtent },
                { x,  m_GridExtent }
            );
        }

        for (float y = -m_GridExtent; y <= m_GridExtent; y += m_GridSize)
        {
            debugRenderer.drawLine(
                { -m_GridExtent, y },
                { m_GridExtent,  y }
            );
        }
    }

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

    Entity* selectedEntity =
        editorContext.getSelectedEntity();

    if (!selectedEntity ||
        !scene->containsEntity(selectedEntity) ||
        selectedEntity->isDestroyed())
    {
        return;
    }

    auto* transform =
        selectedEntity->getComponent<TransformComponent>();

    if (!transform)
        return;

    glm::vec2 selectionSize =
        transform->scale;

    if (auto* collider =
        selectedEntity->getComponent<ColliderComponent>())
    {
        selectionSize = collider->size;
    }

    selectionSize += glm::vec2(
        4.0f,
        4.0f
    );

    debugRenderer.drawRect(
        transform->position -
        selectionSize * 0.5f,
        selectionSize
    );

    glm::vec2 outerSize =
        selectionSize +
        glm::vec2(
            4.0f,
            4.0f
        );

    debugRenderer.drawRect(
        transform->position -
        outerSize * 0.5f,
        outerSize
    );
}

void GameLayer::handleViewportReset()
{
    if (viewportPanel.consumeResetCameraRequest())
    {
        scene->camera.position = { 0.0f, 0.0f };
        scene->camera.zoom = 1.0f;
    }
}

Entity* GameLayer::duplicateEntity(Entity* source)
{
    if (!source ||
        source->isDestroyed() ||
        !scene->containsEntity(source))
    {
        return nullptr;
    }

    Entity* copy =
        scene->createEntity(
            source->getName() + " Copy"
        );

    if (auto* sourceTransform =
        source->getComponent<TransformComponent>())
    {
        auto* transform =
            copy->addComponent<TransformComponent>();

        *transform = *sourceTransform;

        transform->position.x += 32.0f;
        transform->position.y += 32.0f;
    }

    if (auto* sourceSprite =
        source->getComponent<SpriteComponent>())
    {
        copy->addComponent<SpriteComponent>(
            sourceSprite->getTextureID(),
            sourceSprite->getTexture()
        );
    }

    if (auto* sourceVelocity =
        source->getComponent<VelocityComponent>())
    {
        auto* velocity =
            copy->addComponent<VelocityComponent>();

        *velocity = *sourceVelocity;
    }

    if (auto* sourceCollider =
        source->getComponent<ColliderComponent>())
    {
        auto* collider =
            copy->addComponent<ColliderComponent>();

        *collider = *sourceCollider;
    }

    if (auto* sourceController =
        source->getComponent<PlayerControllerComponent>())
    {
        auto* controller =
            copy->addComponent<PlayerControllerComponent>();

        *controller = *sourceController;
    }

    if (source->hasComponent<PlayerTag>())
    {
        copy->addComponent<PlayerTag>();
    }

    editorContext.setSelectedEntity(copy);

    return copy;
}

void GameLayer::updateEditorPanels()
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

    hierarchyPanel.clear();

    scene->forEach([&](Entity* entity)
        {
            hierarchyPanel.addEntity(entity);
        });

    assetBrowserPanel.clear();

    assetBrowserPanel.addAsset("player");
    assetBrowserPanel.addAsset("test");
    assetBrowserPanel.addAsset("office");
    assetBrowserPanel.addAsset("fallback");
}

void GameLayer::handleSceneEditorRequests()
{
    if (sceneEditorPanel.isRenameSceneRequested())
    {
        sceneManager.renameActiveScene(
            sceneEditorPanel.getRequestedSceneName()
        );

        sceneEditorPanel.resetRenameSceneRequest();
    }

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
        Entity* entity = createDefaultEntity("New Entity");

        if (entity)
        {
            editorContext.setSelectedEntity(entity);
        }

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
}

void GameLayer::handleHierarchyRequests()
{
    if (hierarchyPanel.isCreateEntityRequested())
    {
        Entity* entity = createDefaultEntity("New Entity");

        if (entity)
        {
            editorContext.setSelectedEntity(entity);
        }

        hierarchyPanel.resetCreateEntityRequest();
    }

    if (Entity* source = hierarchyPanel.getDuplicateEntity())
    {
        duplicateEntity(source);

        hierarchyPanel.resetDuplicateEntityRequest();
    }

    if (Entity* target =
        hierarchyPanel.getFocusEntity())
    {
        if (!target->isDestroyed() &&
            scene->containsEntity(target))
        {
            auto* transform =
                target->getComponent<TransformComponent>();

            if (transform)
            {
                scene->camera.position =
                    transform->position;
            }
        }

        hierarchyPanel.resetFocusEntityRequest();
    }
}

void GameLayer::handleAssetBrowserRequests()
{
    if (!assetBrowserPanel.isApplyAssetRequested())
        return;

    Entity* selectedEntity =
        editorContext.getSelectedEntity();

    if (selectedEntity &&
        scene->containsEntity(selectedEntity) &&
        !selectedEntity->isDestroyed())
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

void GameLayer::refreshCachedEntities()
{
    scene->cleanupDestroyedEntities();

    player = scene->findEntityByName("Player");
    test = scene->findEntityByName("Test");
}

void GameLayer::onRender()
{
    if (!scene)
        return;

    handleViewportZoom();

    viewportPanel.beginRender();

    scene->onRender();

    if (editorUI.isDebugRendererVisible())
    {
        debugRenderer.render();
    }

    viewportPanel.endRender();

    editorUI.render();

    renderMainMenuUI();
    renderGameStateUI();
    renderPauseUI();

    if (editorUI.isViewportVisible())
    {
        viewportPanel.render();

        handleViewportSelection();

        handleEntityDragging();
    }

    handleViewportReset();

    if (editorUI.isDebugOverlayVisible())
        debugOverlay.render();

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

    preferencesPanel.setVisible(editorUI.isPreferencesVisible());

    if (editorUI.isPreferencesVisible()) 
    {
        preferencesPanel.render();
    }
}

}