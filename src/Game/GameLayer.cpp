#include "Axiom/Experimental/Game/GameLayer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Core/Paths.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp" 
#include "Axiom/Scene/Components/VelocityComponent.hpp" 
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp" 
#include "Axiom/Scene/Components/PlayerTag.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"
#include "Axiom/Input/Input.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

namespace Axiom {

GameLayer::GameLayer()
{

    playerTex = ResourceManager::getTexture(
        Paths::getAsset("player.png")
    );

    testTex = ResourceManager::getTexture(
        Paths::getAsset("test.png")
    );

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

    test->addComponent<SpriteComponent>(testTex);

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

    player->addComponent<SpriteComponent>(playerTex);

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
            // TODO(0.6.x):
            // Move player/test ownership fully into Gameplay scene.
            // GameLayer should not keep raw pointers across scene switches.

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

    gameContext.dt = dt;

    if (gameState == GameState::Gameplay)
    {
        gameContext.nightTime += dt;

        powerSystem.update(gameContext);
        
        enemySystem.update(gameContext);

        if (gameContext.nightTime >= gameContext.nightDuration)
        {
            std::cout << "WIN" << std::endl;
            gameContext.win = true;
            gameState = GameState::Win;
        }

        if (gameContext.gameOver)
        {
            std::cout << "GAME OVER" << std::endl;
            gameState = GameState::GameOver;
        }
    }

    auto* playerTransform = player->getComponent<TransformComponent>();
    glm::vec2 oldPlayerPosition = playerTransform->position;

    scene->onUpdate(dt);

    playerTransform->rotation += 90.0f * dt;

    collisionSystem.update(*scene);

    auto* testTransform = test->getComponent<TransformComponent>();

    if (testTransform)
    {
        // TODO(0.6.6):
        // Move collision response from GameLayer into CollisionSystem.
        
        float dx = playerTransform->position.x - testTransform->position.x;
        float dy = playerTransform->position.y - testTransform->position.y;
        
        if (std::abs(dx) < 320.0f && std::abs(dy) < 320.0f)
        {
            playerTransform->position = oldPlayerPosition;
        }
    }
          
    scene->followCamera(player, dt);

}

void GameLayer::onRender()
{
    Renderer::clear();

    scene->onRender();

}

}