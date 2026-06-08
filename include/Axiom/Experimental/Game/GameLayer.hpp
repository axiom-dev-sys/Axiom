#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Axiom/Core/Layer.hpp"
#include "Axiom/Input/Input.hpp"
#include "Axiom/Core/Time.hpp"
#include "Axiom/Core/Paths.hpp"

#include "Axiom/Experimental/PowerSystem.hpp"
#include "Axiom/Experimental/UISystem.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Experimental/Game/GameContext.hpp"
#include "Axiom/Renderer/Texture.hpp"

#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Renderer/Shader.hpp"

#include "Axiom/Scene/Systems/MovementSystem.hpp"
#include "Axiom/Scene/Systems/CameraFollowSystem.hpp"

namespace Axiom {

class GameLayer : public Axiom::Layer
{
public:
    GameLayer();

    void onUpdate(float dt) override;
    void onRender() override;

private:
    float winTimer = 0.0f;
    float visualTimer = 0.0f;
    bool tabPressed = false;

    Axiom::Scene scene;
    Axiom::Entity* player = nullptr;
    Axiom::Entity* test = nullptr;
    Axiom::TransformComponent* transform = nullptr;
    Axiom::GameContext ctx;

    Axiom::PowerSystem power;
    Axiom::UISystem ui;

    Axiom::Texture* playerTex = nullptr;
    Axiom::Texture* testTex = nullptr;

    MovementSystem movementSystem;
    CameraFollowSystem cameraFollowSystem;
};

}