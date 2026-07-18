#pragma once

#include "Axiom/Core/Layer.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/SceneManager.hpp"
#include "Axiom/Scene/Systems/CollisionSystem.hpp"
#include "Axiom/Experimental/Game/GameState.hpp"
#include "Axiom/Experimental/Game/GameContext.hpp"
#include "Axiom/Experimental/EnemySystem.hpp"
#include "Axiom/Experimental/PowerSystem.hpp"
#include "Axiom/DebugTools/DebugOverlay.hpp"
#include "Axiom/DebugTools/DebugRenderer.hpp"
#include "Axiom/Editor/Panels/InspectorPanel.hpp"
#include "Axiom/Editor/Panels/HierarchyPanel.hpp"
#include "Axiom/Editor/Panels/SceneEditorPanel.hpp"
#include "Axiom/Editor/Panels/AssetBrowserPanel.hpp"
#include "Axiom/Editor/Panels/ConsolePanel.hpp"
#include "Axiom/Editor/Panels/StatisticsPanel.hpp"
#include "Axiom/Editor/EditorContext.hpp"
#include "Axiom/Editor/EditorUI.hpp"
#include "Axiom/Editor/Panels/PreferencesPanel.hpp"
#include "Axiom/Editor/Viewport/ViewportPanel.hpp"

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <utility>

namespace Axiom {

    class Application;

class GameLayer : public Axiom::Layer
{
public:
    GameLayer(Application* application);

    void onUpdate(float dt) override;
    void onRender() override;
    bool isExitRequested() const;

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
    Application* m_Application = nullptr;

    void initializeDefaultScene();

    Entity* createDefaultEntity(const std::string& name);
    Entity* createPlayerEntity();
    Entity* createTestEntity();
    Entity* duplicateEntity(Entity* source);
    Entity* findPlayer() const;

    void handleInteractions();
    void refreshSceneReferences();
    void handleRuntimeControls();
    void startRuntime();
    void stopRuntime();
    void resetGameSession();
    void handleGameStateTransitions();
    void handleSceneSerialization();
    void handleEditorTools();
    void updateInspectorInfo();
    void updateEditorStatus(float dt);
    void updateGameplay(float dt);
    void handleGameplayPause();
    void handleRuntimeSceneSwitch();
    void updateGameSystems(float dt);
    void renderGameStateUI();
    void renderPauseUI();
    void returnToMenuFromPause();
    void startGameFromMenu();
    void returnToMenu();
    void setActiveScene(const std::string& name, std::shared_ptr<Scene> newScene);
    void enterEditor();
    void enterRuntime();
    void enterMenu();
    void resetEditorInteractionState();
    void handleViewportCamera(float dt);
    void handleSceneEditingInput(float dt);
    void handleViewportSelection();
    void handleEntityDragging();
    void handleViewportZoom();
    void handleEditorShortcuts();
    void updateDebugRenderer();
    void handleViewportReset();
    void updateEditorPanels();
    void handleSceneEditorRequests();
    void handleHierarchyRequests();
    void handleAssetBrowserRequests();
    void refreshCachedEntities();
    void handleGameRestart();
    
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
    AssetBrowserPanel assetBrowserPanel;
    ConsolePanel consolePanel;
    StatisticsPanel statisticsPanel;
    EditorContext editorContext;
    EditorUI editorUI;
    ViewportPanel viewportPanel;
    PreferencesPanel preferencesPanel;
    GameState gameState = GameState::Gameplay;

    std::shared_ptr<Scene> editorScene;
    std::shared_ptr<Scene> runtimeScene;

    std::vector<std::pair<std::string, std::shared_ptr<Scene>>> editorScenes;

    bool pauseKeyWasPressed = false;
    bool sceneSwitchKeyWasPressed = false;
    bool cameraKeyWasPressed = false;
    bool doorKeyWasPressed = false;
    bool f3PressedLastFrame = false;
    bool f4PressedLastFrame = false;
    bool f5PressedLastFrame = false;
    bool f6PressedLastFrame = false;
    bool f7PressedLastFrame = false;
    bool f8PressedLastFrame = false;

    Entity* player = nullptr;
    Entity* test = nullptr;

    bool m_ViewportPanning = false;

    double m_LastMouseX = 0.0;
    double m_LastMouseY = 0.0;

    bool m_SnapEnabled = true;
    float m_GridSize = 64.0f;

    bool m_GridVisible = true;
    bool m_GridKeyPressedLastFrame = false;

    bool m_SnapKeyPressedLastFrame = false;

    bool m_LeftArrowPressedLastFrame = false;
    bool m_RightArrowPressedLastFrame = false;
    bool m_UpArrowPressedLastFrame = false;
    bool m_DownArrowPressedLastFrame = false;

    bool m_DeleteKeyPressedLastFrame = false;

    bool m_EntityDragging = false;

    bool m_DuplicateKeyPressedLastFrame = false;

    bool m_FocusKeyPressedLastFrame = false;

    bool m_SaveKeyPressedLastFrame = false;

    bool m_LoadKeyPressedLastFrame = false;

    bool restartKeyWasPressed = false;

    Entity* m_DraggedEntity = nullptr;
};

}