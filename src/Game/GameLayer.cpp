#include "Axiom/Experimental/Game/GameLayer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Resource/AssetRegistry.hpp"
#include "Axiom/Core/Paths.hpp"
#include "Axiom/Core/Log.hpp"
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
#include "Axiom/Core/Version.hpp"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <cmath>
#include <string>

namespace Axiom {

GameLayer::GameLayer(Application* application)
    : m_Application(application)
{
    initializeDefaultScene();

    Log::info("Axiom editor started");
    Log::info("Gameplay scene loaded");
    Log::info("ResourceManager initialized");
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

    if (gameContext.cameraOn)
    {
        if (Input::isKeyPressed(GLFW_KEY_1))
        {
            gameContext.cameraView = CameraView::Camera1;
        }

        if (Input::isKeyPressed(GLFW_KEY_2))
        {
            gameContext.cameraView = CameraView::Camera2;
        }
    }

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
        office = nullptr;
        camera = nullptr;
        return;
    }

    player = scene->findEntityByName("Player");
    test = scene->findEntityByName("Test");
    office = scene->findEntityByName("Office");
    camera = scene->findEntityByName("Camera");

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

    gameState = GameState::Menu;
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

    gameContext.enemyState = EnemyState::Hidden;

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

        Log::info("Scene saved");
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

        Log::info("Scene loaded");
    }
}

void GameLayer::handleEditorTools()
{
    updateEditorPanels();

    handleSceneEditorRequests();
    handleHierarchyRequests();
    
    if (inspectorPanel.isDestroyEntityRequested())
    {
        editorEntityOperations.destroyEntity(
            editorContext.getSelectedEntity(),
            *scene,
            editorContext
        );

        inspectorPanel.resetDestroyEntityRequest();
    }

    if (inspectorPanel.isAddVelocityRequested())
    {
        editorComponentOperations.addVelocityComponent(
            editorContext.getSelectedEntity()
        );

        inspectorPanel.resetAddVelocityRequest();
    }

    if (inspectorPanel.isRemoveVelocityRequested())
    {
        editorComponentOperations.removeVelocityComponent(
            editorContext.getSelectedEntity()
        );

        inspectorPanel.resetRemoveVelocityRequest();
    }

    if (inspectorPanel.isAddColliderRequested())
    {
        editorComponentOperations.addColliderComponent(
            editorContext.getSelectedEntity()
        );

        inspectorPanel.resetAddColliderRequest();
    }

    if (inspectorPanel.isRemoveColliderRequested())
    {
        editorComponentOperations.removeColliderComponent(
            editorContext.getSelectedEntity()
        );

        inspectorPanel.resetRemoveColliderRequest();
    }

    if (inspectorPanel.isAddSpriteRequested())
    {
        editorComponentOperations.addSpriteComponent(
            editorContext.getSelectedEntity()
        );

        inspectorPanel.resetAddSpriteRequest();
    }

    if (inspectorPanel.isRemoveSpriteRequested())
    {
        editorComponentOperations.removeSpriteComponent(
            editorContext.getSelectedEntity()
        );

        inspectorPanel.resetRemoveSpriteRequest();
    }

    if (assetBrowserPanel.isApplyAssetRequested())
    {
        const std::string& assetID =
            assetBrowserPanel.getSelectedAsset();

        if (!assetID.empty())
        {
            editorComponentOperations.setSpriteTexture(
                editorContext.getSelectedEntity(),
                assetID
            );
        }

        assetBrowserPanel.resetApplyAssetRequest();
    }

    refreshCachedEntities();

    editorContext.validateSelection();
}

void GameLayer::updateEditorStatus(float dt)
{
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
        getPlayerPosition(),
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
        editorTransformController.isSnapEnabled()
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

void GameLayer::handleGameStateTransitions()
{
    if (gameContext.win)
    {
        gameState = GameState::Win;
        Log::info("YOU WIN");
    }

    if (gameContext.gameOver)
    {
        gameState = GameState::GameOver;
        Log::info("GAME OVER");
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
        ImGui::Text("Congratulations!");
    }
    else
    {
        ImGui::Text("GAME OVER");
        ImGui::Text("Try Again!");
    }

    ImGui::Separator();

    ImGui::Spacing();
    
    if (ImGui::Button("Restart", ImVec2(280.0f, 40.0f)))
    {
        stopRuntime();
        startRuntime();

        m_Application->play();
    }

    ImGui::Spacing();

    if (ImGui::Button("Return to Menu", ImVec2(280.0f, 40.0f)))
    {
        returnToMenu();
    }

    ImGui::Spacing();

    ImGui::Text("Shortcut: R");

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
        m_Application->play();
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

    ImGui::TextDisabled("Gameplay Prototype");
    ImGui::TextDisabled("Version %s", AXIOM_VERSION);
    
    ImGui::Spacing();

    if (ImGui::Button(
        "Start Game",
        ImVec2(280.0f, 40.0f)
    ))
    {
        startGameFromMenu();
    }

    ImGui::Spacing();

    ImGui::Text("Difficulty");

    int difficultyIndex = 1;

    switch (gameContext.difficulty)
    {
    case Difficulty::Easy:
        difficultyIndex = 0;
        break;

    case Difficulty::Normal:
        difficultyIndex = 1;
        break;

    case Difficulty::Hard:
        difficultyIndex = 2;
        break;
    }

    if (ImGui::RadioButton("Easy", difficultyIndex == 0))
    {
        gameContext.difficulty = Difficulty::Easy;
    }

    if (ImGui::RadioButton("Normal", difficultyIndex == 1))
    {
        gameContext.difficulty = Difficulty::Normal;
    }

    if (ImGui::RadioButton("Hard", difficultyIndex == 2))
    {
        gameContext.difficulty = Difficulty::Hard;
    }

    ImGui::Spacing();
    ImGui::Separator();

    ImGui::Text("Selected:");

    ImGui::SameLine();

    switch (gameContext.difficulty)
    {
    case Difficulty::Easy:
        ImGui::TextColored(
            ImVec4(0.3f, 1.0f, 0.3f, 1.0f),
            "Easy"
        );
        break;

    case Difficulty::Normal:
        ImGui::TextColored(
            ImVec4(1.0f, 1.0f, 0.3f, 1.0f),
            "Normal"
        );
        break;

    case Difficulty::Hard:
        ImGui::TextColored(
            ImVec4(1.0f, 0.4f, 0.4f, 1.0f),
            "Hard"
        );
        break;
    }


    ImGui::Spacing();

    if (ImGui::Button(
        "Exit to Editor",
        ImVec2(280.0f, 40.0f)
    ))
    {
        exitToEditor();
    }

    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextDisabled("Powered by Axiom Engine");

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

    updateGameplayPresentation();

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

void GameLayer::updateGameplayPresentation()
{
    if (!office || office->isDestroyed())
    {
        return;
    }

    if (!camera || camera->isDestroyed())
    {
        return;
    }

    const bool powerOut = gameContext.power <= 0.0f;
    const bool cameraVisible =
        gameContext.cameraOn && !powerOut;

    office->setActive(!cameraVisible);
    camera->setActive(cameraVisible);

    if (cameraVisible)
    {
        auto* cameraSprite =
            camera->getComponent<SpriteComponent>();

        if (!cameraSprite)
        {
            return;
        }

        std::string cameraTextureID;

        switch (gameContext.cameraView)
        {
        case CameraView::Camera1:
            cameraTextureID =
                gameContext.enemyState == EnemyState::Camera1
                ? "camera_1_enemy"
                : "camera_1_empty";
            break;

        case CameraView::Camera2:
            cameraTextureID =
                gameContext.enemyState == EnemyState::Camera2
                ? "camera_2_enemy"
                : "camera_2_empty";
            break;

        case CameraView::None:
        default:
            cameraTextureID = "camera_1_empty";
            break;
        }

        if (cameraSprite->getTextureID() != cameraTextureID)
        {
            cameraSprite->setTexture(
                cameraTextureID,
                ResourceManager::getTexture(cameraTextureID)
            );
        }

        return;
    }

    auto* sprite =
        office->getComponent<SpriteComponent>();

    if (!sprite)
    {
        return;
    }

    std::string textureID = "office";

    if (powerOut)
    {
        textureID = "office_empty";
    }
    else if (gameContext.doorClosed)
    {
        textureID = "office_door_closed";
    }
    else
    {
        switch (gameContext.enemyState)
        {
        case EnemyState::OfficeFar:
            textureID = "office_enemy_far";
            break;

        case EnemyState::OfficeClose:
            textureID = "office_enemy_close";
            break;

        default:
            textureID = "office";
            break;
        }

        if (sprite->getTextureID() == textureID)
        {
            return;
        }
    }
    
    sprite->setTexture(
        textureID,
        ResourceManager::getTexture(textureID)
    );
}

void GameLayer::initializeDefaultScene()
{
    gameplayScene = std::make_shared<Scene>();
    menuScene = std::make_shared<Scene>();

    editorScene = gameplayScene;
    runtimeScene = nullptr;

    scene = gameplayScene;
    sceneManager.setActiveScene("Gameplay", scene);

    editorContext.setScene(scene.get());

    office = createOfficeEntity();
    camera = createCameraEntity();

    test = createTestEntity();
    player = createPlayerEntity();

    sceneManager.addScene("Gameplay", gameplayScene);
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

Entity* GameLayer::createOfficeEntity()
{
    if (!scene)
    {
        return nullptr;
    }

    Entity* entity =
        scene->createEntity("Office");

    auto* transform =
        entity->addComponent<TransformComponent>();

    transform->position = { 0.0f, 0.0f };
    transform->scale = { 1280.0f, 720.0f };
    transform->rotation = 0.0f;

    entity->addComponent<SpriteComponent>(
        "office",
        ResourceManager::getTexture("office")
    );

    return entity;
}

Entity* GameLayer::createCameraEntity()
{
    if (!scene)
    {
        return nullptr;
    }

    Entity* entity =
        scene->createEntity("Camera");

    auto* transform =
        entity->addComponent<TransformComponent>();

    transform->position = { 0.0f, 0.0f };
    transform->scale = { 1280.0f, 720.0f };
    transform->rotation = 0.0f;

    entity->addComponent<SpriteComponent>(
        "camera_1_empty",
        ResourceManager::getTexture("camera_1_empty")
    );

    entity->setActive(false);

    return entity;
}

void GameLayer::setActiveScene(const std::string& name, std::shared_ptr<Scene> newScene)
{
    scene = newScene;

    sceneManager.setActiveScene(name, scene);

    if (m_Application->getMode() == EngineMode::Edit)
    {
        editorScene = scene;
    }

    editorContext.setScene(scene.get());

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
    editorInteractionSystem.stopDragging();

    editorCameraController.reset();

    editorTransformController.resetInputState();

    editorCommandController.resetInputState();
}

void GameLayer::handleViewportCamera(float dt)
{
    if (m_Application->getMode() != EngineMode::Edit)
        return;

    if (!editorUI.isViewportVisible())
        return;

    if (!scene)
        return;

    editorCameraController.update(
        viewportPanel,
        *scene,
        dt
    );
}

void GameLayer::handleSceneEditingInput(float dt)
{
    if (m_Application->getMode() != EngineMode::Edit)
        return;

    if (ImGui::GetIO().WantTextInput)
    {
        return;
    }

    editorTransformController.updateSnapToggle();
    editorTransformController.updateGridToggle();

    if (!editorUI.isViewportVisible() ||
        !viewportPanel.isFocused())
    {
        return;
    }

    editorInteractionSystem.updateDelete(
        editorContext,
        *scene
    );

    if (editorInteractionSystem.consumeDuplicateRequest())
    {
        editorEntityOperations.duplicateEntity(
            editorContext.getSelectedEntity(),
            *scene,
            editorContext
        );
    }

    if (editorCommandController.consumeSaveRequest())
    {
        editorUI.requestSaveScene();
    }

    if (editorCommandController.consumeLoadRequest())
    {
        editorUI.requestLoadScene();
    }

    editorInteractionSystem.updateFocus(
        editorContext,
        *scene
    );

    if (!editorInteractionSystem.isDragging())
    {
        editorTransformController.update(
            editorContext,
            *scene,
            dt
        );
    }
}

void GameLayer::handleViewportSelection()
{
    if (m_Application->getMode() != EngineMode::Edit)
        return;

    if (!editorUI.isViewportVisible())
        return;

    if (!scene)
        return;

    editorInteractionSystem.updateSelection(
        editorContext,
        viewportPanel,
        *scene
    );
}

void GameLayer::handleEntityDragging()
{
    if (m_Application->getMode() != EngineMode::Edit)
        return;

    if (!scene)
        return;

    editorInteractionSystem.updateDragging(
        viewportPanel,
        *scene
    );
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

    if (!scene)
        return;

    if (!editorUI.isDebugRendererVisible())
        return;

    if (editorTransformController.isGridVisible())
    {
        const float gridExtent = 2048.0f;

        const float gridSize =
            editorTransformController.getGridSize();

        for (float x = -gridExtent; x <= gridExtent; x += gridSize)
        {
            debugRenderer.drawLine(
                { x, -gridExtent },
                { x,  gridExtent }
            );
        }

        for (float y = -gridExtent; y <= gridExtent; y += gridSize)
        {
            debugRenderer.drawLine(
                { -gridExtent, y },
                { gridExtent,  y }
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

void GameLayer::updateEditorPanels()
{
    hierarchyPanel.setEditorContext(&editorContext);
    inspectorPanel.setEditorContext(&editorContext);
    sceneEditorPanel.setEditorContext(&editorContext);
    assetBrowserPanel.setEditorContext(&editorContext);
    viewportPanel.setEditorContext(&editorContext);

    statisticsPanel.setEditorContext(
        &editorContext
    );

    statisticsPanel.setSceneManager(
        &sceneManager
    );

    sceneEditorPanel.setSceneManager(&sceneManager);
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
        std::string name =
            "New Scene " + std::to_string(sceneManager.getScenes().size() + 1);

        auto newScene =
            sceneManager.createScene(name);

        if (newScene)
        {
            setActiveScene(
                name,
                newScene
            );
        }

        sceneEditorPanel.resetNewSceneRequest();
    }

    if (sceneEditorPanel.isSwitchSceneRequested())
    {
        const std::string& name =
            sceneEditorPanel.getRequestedSceneSwitchName();

        if (sceneManager.switchScene(name))
        {
            setActiveScene(
                sceneManager.getActiveSceneName(),
                sceneManager.getActiveScene()
            );
        }

        sceneEditorPanel.resetSwitchSceneRequest();
    }

    if (sceneEditorPanel.isDeleteSceneRequested())
    {
        std::string nextSceneName;

        auto nextScene =
            sceneManager.removeActiveScene(
                nextSceneName
            );

        if (nextScene)
        {
            setActiveScene(
                nextSceneName,
                nextScene
            );
        }

        sceneEditorPanel.resetDeleteSceneRequest();
    }

    if (sceneEditorPanel.isCreateEntityRequested())
    {
        editorEntityOperations.createEntity(
            *scene,
            editorContext
        );

        sceneEditorPanel.resetCreateEntityRequest();
    }

    if (sceneEditorPanel.isDestroyEntityRequested())
    {
        editorEntityOperations.destroyEntity(
            editorContext.getSelectedEntity(),
            *scene,
            editorContext
        );

        sceneEditorPanel.resetDestroyEntityRequest();
    }
}

void GameLayer::handleHierarchyRequests()
{
    if (hierarchyPanel.isCreateEntityRequested())
    {
        editorEntityOperations.createEntity(
            *scene,
            editorContext
        );

        hierarchyPanel.resetCreateEntityRequest();
    }

    if (Entity* source = hierarchyPanel.getDuplicateEntity())
    {
        editorEntityOperations.duplicateEntity(source,
            *scene,
            editorContext
        );

        hierarchyPanel.resetDuplicateEntityRequest();
    }

    if (Entity* target =
        hierarchyPanel.getFocusEntity())
    {
        editorInteractionSystem.focusEntity(
            target,
            *scene
        );

        hierarchyPanel.resetFocusEntityRequest();
    }
}

void GameLayer::refreshCachedEntities()
{
    if (!scene)
        return;

    scene->cleanupDestroyedEntities();

    player = scene->findEntityByName("Player");
    test = scene->findEntityByName("Test");
    office = scene->findEntityByName("Office");
    camera = scene->findEntityByName("Camera");
}

void GameLayer::renderGameplayHUD()
{
    if (!m_Application->isPlaying())
        return;

    if (gameState != GameState::Gameplay)
        return;

    if (sceneManager.getActiveSceneName() != "Gameplay")
        return;

    const ImVec2 viewportPosition =
        viewportPanel.getBoundsMin();

    ImGui::SetNextWindowPos(
        ImVec2(
            viewportPosition.x + 16.0f,
            viewportPosition.y + 16.0f
        ),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoSavedSettings;

    ImGui::SetNextWindowPos(
        ImVec2(180.0f, 120.0f),
        ImGuiCond_Always
    );

    ImGui::SetNextWindowSize(
        ImVec2(220.0f, 150.0f),
        ImGuiCond_Always
    );

    ImGui::SetNextWindowBgAlpha(0.75f);

    ImGui::Begin("Gameplay Status", nullptr, flags);

    ImGui::Text("STATUS");
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text(
        "Power: %.0f%%",
        gameContext.power
    );

    ImGui::ProgressBar(
        gameContext.power / 100.0f,
        ImVec2(-1.0f, 0.0f)
    );

    ImGui::Text(
        "Night Time: %.0f / %.0f",
        gameContext.nightTime,
        gameContext.nightDuration
    );

    ImGui::Text(
        "Door: %s",
        gameContext.doorClosed ? "Closed" : "Open"
    );

    ImGui::End();

    ImGui::SetNextWindowPos(
        ImVec2(810.0f, 120.0f),
        ImGuiCond_Always
    );

    ImGui::SetNextWindowBgAlpha(0.75f);

    ImGui::Begin("Gameplay Controls", nullptr, flags);

    ImGui::Text("CURRENT MODE");
    ImGui::Separator();
    ImGui::Spacing();

    if (gameContext.cameraOn)
    {
        switch (gameContext.cameraView)
        {
        case CameraView::Camera1:
            ImGui::Text("Camera 1");
            break;

        case CameraView::Camera2:
            ImGui::Text("Camera 2");
            break;

        default:
            ImGui::Text("Camera");
            break;
        }
    }
    else
    {
        ImGui::Text("Office");
    }
    
    ImGui::Separator();

    ImGui::Text("CONTROLS");
    ImGui::Spacing();

    if (gameContext.cameraOn)
    {
        ImGui::Text("[1] Camera 1");
        ImGui::Text("[2] Camera 2");
        ImGui::Text("[C] Return to Office");
    }
    else
    {
        ImGui::Text("[E] Toggle Door");
        ImGui::Text("[C] Open Cameras");
    }

    if (debugOverlay.isVisible())
    {
        ImGui::Separator();
        ImGui::Text("DEBUG");
        ImGui::Spacing();

        ImGui::Text("Enemy:");

        switch (gameContext.enemyState)
        {
        case EnemyState::Hidden:
            ImGui::SameLine();
            ImGui::Text("Hidden");
            break;

        case EnemyState::Camera2:
            ImGui::SameLine();
            ImGui::Text("Camera 2");
            break;

        case EnemyState::Camera1:
            ImGui::SameLine();
            ImGui::Text("Camera 1");
            break;

        case EnemyState::OfficeFar:
            ImGui::SameLine();
            ImGui::Text("Office Far");
            break;

        case EnemyState::OfficeClose:
            ImGui::SameLine();
            ImGui::Text("Office Close");
            break;

        case EnemyState::Attack:
            ImGui::SameLine();
            ImGui::Text("Attack");
            break;

        default:
            ImGui::SameLine();
            ImGui::Text("Unknown");
            break;
        }

        ImGui::Text(
            "Camera System: %s",
            gameContext.cameraOn ? "On" : "Off"
        );
    }

    ImGui::End();
}

void GameLayer::onRender()
{
    if (!scene)
        return;

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

        editorCameraController.updateZoom(
            viewportPanel,
            *scene
        );

        if (viewportPanel.consumeResetCameraRequest())
        {
            editorCameraController.resetCamera(
                *scene
            );
        }

        renderGameplayHUD();

        handleViewportSelection();
        handleEntityDragging();
    }
    
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