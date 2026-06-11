#pragma once

#include "Axiom/Core/Layer.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Renderer/Texture.hpp"

namespace Axiom {

class GameLayer : public Axiom::Layer
{
public:
    GameLayer();

    void onUpdate(float dt) override;
    void onRender() override;

private:
    Scene scene;

    Entity* player = nullptr;
    Entity* test = nullptr;

    Axiom::Texture* playerTex = nullptr;
    Axiom::Texture* testTex = nullptr;

};

}