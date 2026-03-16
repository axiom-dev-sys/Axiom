#pragma once
#include "Axiom/Core/Layer.hpp"
#include "Axiom/Events/Event.hpp"
#include "Axiom/Events/KeyEvent.hpp"
#include "Axiom/Input/Input.hpp"
#include "Axiom/Scene/Scene.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

class GameLayer : public Axiom::Layer
{
public:
    GameLayer()
        : Layer("GameLayer")
    {
        player = scene.createEntity("Player");
    }

    void onEvent(Axiom::Event& event) override
    {
        if (event.getEventType() == Axiom::EventType::KeyPressed)
        {
            auto& e = (Axiom::KeyPressedEvent&)event;
            std::cout << "Key pressed in GameLayer: " << e.getKeyCode() << std::endl;
        }
    }

    void onUpdate() override
    {
        if (Axiom::Input::isKeyPressed(GLFW_KEY_SPACE))
        {
            player->getTransform().x += 0.01f;

            std::cout << "Press X: " << player->getTransform().x << std::endl;
        }
    }

private:

    Axiom::Scene scene;
    Axiom::Entity* player;
};