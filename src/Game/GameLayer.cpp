#include "Axiom/Experimental/Game/GameLayer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Camera/Camera.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Core/Window.hpp"
#include "Axiom/Core/Log.hpp"

namespace Axiom {

GameLayer::GameLayer()
{

    officeTex = ResourceManager::getTexture(
        Paths::getAsset("office.png")
    );

    player = scene.createEntity("Player");

    auto* playerTransform = player->addComponent<TransformComponent>();

    player->addComponent<SpriteComponent>(officeTex);

    auto test = scene.createEntity("Test");

    auto* transform = test->addComponent<TransformComponent>();
    transform->position = {100.0f, 100.0f};

    test->addComponent<SpriteComponent>(officeTex);

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