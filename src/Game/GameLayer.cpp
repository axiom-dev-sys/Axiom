#include "Axiom/Game/GameLayer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Scene/RenderComponent.hpp"
#include "Axiom/Renderer/Camera.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Scene/SpriteComponent.hpp"
#include "Axiom/Core/Window.hpp"
#include "Axiom/Core/Log.hpp"

namespace Axiom {

GameLayer::GameLayer()
{

    officeTex = ResourceManager::getTexture(
        Axiom::Paths::getAsset("office.png")
    );

    player = scene.createEntity("Player");

    auto* playerTransform = player->addComponent<Transform>();

    auto* playerRender = player->addComponent<RenderComponent>();
    playerRender->texture = officeTex;

    auto entity = scene.createEntity("Test");

    auto transform = entity->addComponent<Transform>();
    transform->position = {100.0f, 100.0f};

    auto render = entity->addComponent<RenderComponent>();
    render->texture = officeTex;

}

void GameLayer::onUpdate(float dt)
{
    ctx.dt = dt;

    float speed = 3.0f * dt;

    if (Input::isKeyPressed(GLFW_KEY_W))
        scene.camera.position.y += speed;

    if (Input::isKeyPressed(GLFW_KEY_S))
        scene.camera.position.y -= speed;

    if (Input::isKeyPressed(GLFW_KEY_A))
        scene.camera.position.x -= speed;

    if (Input::isKeyPressed(GLFW_KEY_D))
        scene.camera.position.x += speed;

    bool tabNow = Input::isKeyPressed(GLFW_KEY_TAB);

    if (tabNow && !tabPressed)
        ctx.cameraOn = !ctx.cameraOn;

    tabPressed = tabNow;

    power.update(ctx);
}

void GameLayer::onRender()
{
    Renderer::clear();

    scene.onRender();
}

}