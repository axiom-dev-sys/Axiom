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
namespace Axiom {

GameLayer::GameLayer()
{

    playerTex = ResourceManager::getTexture(
        Paths::getAsset("player.png")
    );

    testTex = ResourceManager::getTexture(
        Paths::getAsset("test.png")
    );

    test = scene.createEntity("Test");
    
    auto* testTransform = test->addComponent<TransformComponent>();    
    testTransform->position = {500.0f, 0.0f};
    testTransform->scale = {512.0f, 512.0f};
    testTransform->rotation = 0.0f;

    auto* testCollider = test->addComponent<ColliderComponent>();
    testCollider->size = {512.0f, 512.0f};
    testCollider->offset = {0.0f, 0.0f};
    testCollider->isTrigger = true;

    test->addComponent<SpriteComponent>(testTex);

    player = scene.createEntity("Player");

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
    playerCollider->isTrigger = true;

    player->addComponent<SpriteComponent>(playerTex);

}

void GameLayer::onUpdate(float dt)
{

    scene.onUpdate(dt);

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
        // TODO: Fix player movement when pausing with movement keys held
        return;
    }

    auto* playerTransform = player->getComponent<TransformComponent>();

    playerTransform->rotation += 90.0f * dt;

    collisionSystem.update(scene);
          
    scene.followCamera(player, dt);

}

void GameLayer::onRender()
{
    Renderer::clear();

    scene.onRender();

}

}