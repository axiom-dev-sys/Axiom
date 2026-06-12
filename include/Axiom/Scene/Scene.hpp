#pragma once
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Camera/Camera.hpp"
#include "Axiom/Scene/Systems/RenderSystem.hpp"
#include "Axiom/Scene/Systems/MovementSystem.hpp"
#include "Axiom/Scene/Systems/CameraFollowSystem.hpp"
#include "Axiom/Scene/Systems/PlayerInputSystem.hpp"
#include <vector>
#include <memory>
namespace Axiom {

    class Scene
    {
    public:
        Camera camera{};

        void onUpdate(float dt);

        void followCamera(Entity* target, float dt);
        
        void onRender();

        Entity* createEntity(const std::string& name) 
        {

            m_Entities.emplace_back(std::make_unique<Entity>(name));
            
            return m_Entities.back().get();
        }

        template<typename Func>
        void forEach(Func func)
        {
            for (auto& entity : m_Entities)
                func(entity.get());
        }

        size_t getEntityCount() const
        {
            return m_Entities.size();
        }

    private:
        std::vector<std::unique_ptr<Entity>> m_Entities;

        MovementSystem m_MovementSystem;
        CameraFollowSystem m_CameraFollowSystem;
        RenderSystem m_RenderSystem;
        PlayerInputSystem m_PlayerInputSystem;
    };

}