#pragma once
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Camera/Camera.hpp"
#include "Axiom/Scene/Systems/RenderSystem.hpp"
#include "Axiom/Scene/Systems/MovementSystem.hpp"
#include "Axiom/Scene/Systems/CameraFollowSystem.hpp"
#include <vector>
#include <memory>
#include <iostream>
namespace Axiom {

    class Scene
    {
    public:
        Camera camera{};

        void onUpdate(float dt);

        void followCamera(Entity* target);
        
        void onRender();

        Entity* createEntity(const std::string& name) 
        {
            std::cout << "CREATE ENTITY: " << name << std::endl;

            m_Entities.emplace_back(std::make_unique<Entity>(name));

            std::cout << "TOTAL NOW: " << m_Entities.size() << std::endl;
            
            return m_Entities.back().get();
        }

        template<typename Func>
        void forEach(Func func)
        {
            for (auto& entity : m_Entities)
                func(entity.get());
        }

    private:
        std::vector<std::unique_ptr<Entity>> m_Entities;

        MovementSystem m_MovementSystem;
        CameraFollowSystem m_CameraFollowSystem;
        RenderSystem m_RenderSystem;
    };

}