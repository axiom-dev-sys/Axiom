#include "Axiom/Game/GameLayer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Scene/RenderComponent.hpp"
#include "Axiom/Renderer/Camera.hpp"
#include "Axiom/Scene/SpriteComponent.hpp"
#include "Axiom/Core/Window.hpp"
#include "Axiom/Core/Log.hpp"
#include <iostream>

GameLayer::GameLayer()
{
    std::cout << "GameLayer ctor" << std::endl;

    officeTex = Axiom::ResourceManager::getTexture(
        Axiom::Paths::getAsset("office.png")
    );

    player = scene.createEntity("Player");
    transform = player->addComponent<Axiom::Transform>();

    auto sprite1 = player->addComponent<Axiom::SpriteComponent>(officeTex);

    player->addComponent<Axiom::RenderComponent>(
        transform,
        sprite1,
        nullptr
    );

    auto e2 = scene.createEntity("Test");

    auto t2 = e2->addComponent<Axiom::Transform>();
    t2->x = 300.0f;

    auto sprite2 = e2->addComponent<Axiom::SpriteComponent>(officeTex);

    auto r2 = e2->addComponent<Axiom::RenderComponent>(
        t2, sprite2, nullptr
    );

}

void GameLayer::onUpdate(float dt)
{
    ctx.dt = dt;

    float speed = 3.0f * dt;

    if (Axiom::Input::isKeyPressed(GLFW_KEY_W))
        scene.camera.position.y += speed;

    if (Axiom::Input::isKeyPressed(GLFW_KEY_S))
        scene.camera.position.y -= speed;

    if (Axiom::Input::isKeyPressed(GLFW_KEY_A))
        scene.camera.position.x -= speed;

    if (Axiom::Input::isKeyPressed(GLFW_KEY_D))
        scene.camera.position.x += speed;

    bool tabNow = Axiom::Input::isKeyPressed(GLFW_KEY_TAB);

    if (tabNow && !tabPressed)
        ctx.cameraOn = !ctx.cameraOn;

    tabPressed = tabNow;

    power.update(ctx);
}

void GameLayer::onRender()
{
    Axiom::Renderer::clear();
    scene.onRender();
    std::cout << "RENDER CALL" << std::endl;
}