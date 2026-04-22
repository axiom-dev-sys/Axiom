#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Axiom/Core/Layer.hpp"
#include "Axiom/Input/Input.hpp"
#include "Axiom/Core/Time.hpp"
#include "Axiom/Core/Paths.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Transform.hpp"
#include "Axiom/Scene/RenderComponent.hpp"
#include "Axiom/Scene/AnimationComponent.hpp"

#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Renderer/Camera.hpp"

#include "Axiom/Game/EnemySystem.hpp"
#include "Axiom/Game/PowerSystem.hpp"
#include "Axiom/Game/UISystem.hpp"
#include "Axiom/Game/GameContext.hpp"

#include "Axiom/Resource/ResourceManager.hpp"

#include <iostream>
#include <direct.h>


class GameLayer : public Axiom::Layer
{
public:

    int shownEnemyState = 0;

    GameLayer()
        : Layer("GameLayer")
    {
        officeTex = *Axiom::ResourceManager::loadTexture(Axiom::Paths::getAsset("office.png"));
        officeEmpty = *Axiom::ResourceManager::loadTexture(Axiom::Paths::getAsset("office_empty.png"));
        officeFar = *Axiom::ResourceManager::loadTexture(Axiom::Paths::getAsset("office_enemy_far.png"));
        officeClose = *Axiom::ResourceManager::loadTexture(Axiom::Paths::getAsset("office_enemy_close.png"));

        cameraTex = *Axiom::ResourceManager::loadTexture(Axiom::Paths::getAsset("camera.png"));
        camera2Tex = *Axiom::ResourceManager::loadTexture(Axiom::Paths::getAsset("camera_2.png"));

        enemyStartedTex = *Axiom::ResourceManager::loadTexture(Axiom::Paths::getAsset("the_enemy_is_started.png"));

        char buffer[512];
        if (_getcwd(buffer, 512))
        {
            std::cout << "Working dir: " << buffer << std::endl;
        }
        else
        {
            std::cout << "Failed to get working directory\n";
        }

        player = scene.createEntity("Player");
        transform = player->addComponent<Axiom::Transform>();
    }
    
    void onUpdate() override
    {
        Renderer::clear();

        float dt = Time::getDeltaTime();

        ctx.dt = dt;

        bool tabNow = Axiom::Input::isKeyPressed(GLFW_KEY_TAB);

        if (tabNow && !tabPressed)
        {
            ctx.cameraOn = !ctx.cameraOn;
        }

        tabPressed = tabNow;

        ctx.enemyState = Axiom::EnemyState::Idle; // временно

        power.update(ctx);

        Renderer::setCamera(0, 0);

        Renderer::draw(officeTex, { 0,0 });
    }

private:
    float winTimer = 0.0f;
    float visualTimer = 0.0f;
    float gameTime = 0.0f;
    bool fakeEventActive = false;
    float fakeTimer = 0.0f;

    Axiom::Scene scene;
    Axiom::Entity* player = nullptr;
    Axiom::Transform* transform = nullptr;
    Axiom::GameContext ctx;
    PowerSystem power;
    UISystem ui;

    Axiom::Texture officeTex;
    Axiom::Texture cameraTex;
    Axiom::Texture officeEmpty;
    Axiom::Texture officeFar;
    Axiom::Texture officeClose;
    Axiom::Texture camera2Tex;
    Axiom::Texture enemyStartedTex;

    bool isCameraView = false;
    bool cameraSwitch = false;

    bool tabPressed = false;
};