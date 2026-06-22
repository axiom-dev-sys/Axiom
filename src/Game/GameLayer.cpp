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
    playerTransform->rotation = 45.0f;

    auto* playerCollider = player->addComponent<ColliderComponent>();
    playerCollider->size = {128.0f, 128.0f};
    playerCollider->offset = {0.0f, 0.0f};
    playerCollider->isTrigger = false;

    player->addComponent<SpriteComponent>(
        "player",
        ResourceManager::getTexture("player")
    );

    SceneSerializer::save(
        *scene,
        Paths::getSave("scene.txt")
    );

    SceneSerializer::load(
        *scene,
        Paths::getSave("scene.txt")
    );

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

void GameLayer::onUpdate(float dt)
{
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

    debugOverlay.update(dt);

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

    switch (gameState)
    {
    case GameState::Gameplay:
        debugOverlay.setGameState("Gameplay");
        break;

    case GameState::Pause:
        debugOverlay.setGameState("Pause");
        break;

    case GameState::Win:
        debugOverlay.setGameState("Win");
        break;

    case GameState::GameOver:
        debugOverlay.setGameState("Game Over");
        break;
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

        powerSystem.update(gameContext);
        
        enemySystem.update(gameContext);
    }

    auto* playerTransform = player->getComponent<TransformComponent>();
    glm::vec2 oldPlayerPosition = playerTransform->position;

    scene->onUpdate(dt);

    playerTransform->rotation += 90.0f * dt;

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
    Renderer::clear();

    scene->onRender();

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

    debugRenderer.render();
    debugRenderer.clear();

    debugOverlay.render();

}

}