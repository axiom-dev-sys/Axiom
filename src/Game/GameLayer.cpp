#include "Axiom/Experimental/Game/GameLayer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Camera/Camera.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Core/Window.hpp"
#include "Axiom/Core/Log.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp"
#include "Axiom/Scene/Components/PlayerTag.hpp"
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
    player->addComponent<PlayerControllerComponent>();
    player->addComponent<PlayerTag>();
    playerTransform->position = {0.0f, 0.0f};
    playerTransform->scale = {128.0f, 128.0f};
    playerTransform->rotation = 45.0f;

    player->addComponent<SpriteComponent>(playerTex);

}

void GameLayer::onUpdate(float dt)
{
    ctx.dt = dt;

    scene.onUpdate(dt);

    auto* playerTransform =
    player->getComponent<TransformComponent>();

    playerTransform->rotation += 90.0f * dt;
          
    scene.followCamera(player, dt);

}

void GameLayer::onRender()
{
    Renderer::clear();

    scene.onRender();

}

}