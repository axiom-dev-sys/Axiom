#include "Axiom/Experimental/Game/GameLayer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Camera/Camera.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Core/Window.hpp"
#include "Axiom/Core/Log.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include <iostream>
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

    test->addComponent<SpriteComponent>(testTex);

    player = scene.createEntity("Player");

    auto* playerTransform = player->addComponent<TransformComponent>();
    auto* playerVelocity = player->addComponent<VelocityComponent>();
    playerTransform->position = {0.0f, 0.0f};
    playerTransform->scale = {128.0f, 128.0f};
    playerTransform->rotation = 45.0f;
    playerVelocity->velocity.x = 100.0f;

    player->addComponent<SpriteComponent>(playerTex);

}

void GameLayer::onUpdate(float dt)
{
    ctx.dt = dt;

    float speed = 500.0f;

    auto* playerVelocity =
    player->getComponent<VelocityComponent>();

    playerVelocity->velocity = {0.0f, 0.0f};

    if (Input::isKeyPressed(GLFW_KEY_W))
        playerVelocity->velocity.y = speed;

    if (Input::isKeyPressed(GLFW_KEY_S))
        playerVelocity->velocity.y = -speed;

    if (Input::isKeyPressed(GLFW_KEY_A))
        playerVelocity->velocity.x = -speed;

    if (Input::isKeyPressed(GLFW_KEY_D))
        playerVelocity->velocity.x = speed;

    scene.onUpdate(dt);

    auto* playerTransform =
    player->getComponent<TransformComponent>();

    std::cout << "Player: "
          << playerTransform->position.x << " "
          << playerTransform->position.y << "\n";

    playerTransform->rotation += 90.0f * dt;
    
    scene.followCamera(player);

    std::cout << "Camera: "
          << scene.camera.position.x << " "
          << scene.camera.position.y << "\n";

    auto* testTransform =
    test->getComponent<TransformComponent>();

    std::cout << "Test: "
          << testTransform->position.x << " "
          << testTransform->position.y << "\n";

}

void GameLayer::onRender()
{
    Renderer::clear();

    scene.onRender();

}

}