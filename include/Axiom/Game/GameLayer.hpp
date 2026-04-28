#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Axiom/Core/Layer.hpp"
#include "Axiom/Input/Input.hpp"
#include "Axiom/Core/Time.hpp"
#include "Axiom/Core/Paths.hpp"

#include "Axiom/Game/PowerSystem.hpp"
#include "Axiom/Game/UISystem.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Transform.hpp"
#include "Axiom/Game/GameContext.hpp"
#include "Axiom/Renderer/Texture.hpp"

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
    Axiom::Transform* transform = nullptr;
    Axiom::GameContext ctx;

    Axiom::PowerSystem power;
    Axiom::UISystem ui;

    Axiom::Texture* officeTex = nullptr;
};