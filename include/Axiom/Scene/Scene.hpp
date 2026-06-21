#pragma once
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Camera/Camera.hpp"
#include "Axiom/Scene/Systems/RenderSystem.hpp"
#include "Axiom/Scene/Systems/MovementSystem.hpp"
#include "Axiom/Scene/Systems/CameraFollowSystem.hpp"
#include "Axiom/Scene/Systems/PlayerInputSystem.hpp"
#include "Axiom/Scene/Systems/TimerSystem.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdint>
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
            
            Entity* entity = m_Entities.back().get();
            entity->setID(m_NextEntityID++);

            return entity;
        }

        Entity* findEntityByName(const std::string& name)
        {
            for (auto& entity : m_Entities)
            {
                if (!entity->isActive() || entity->isDestroyed())
                continue;
            
                if (entity->getName() == name)
                return entity.get();
            }
            
            return nullptr;
        }

        template<typename Func>
        void forEach(Func func)
        {
            for (auto& entity : m_Entities)
            {
                if (!entity->isActive() || entity->isDestroyed())
                continue;
            
                func(entity.get());
            }
        }

        size_t getEntityCount() const
        {
            return m_Entities.size();
        }

        const std::vector<std::unique_ptr<Entity>>& getEntities() const
        {
            return m_Entities;
        }

        void destroyEntity(Entity* entity)
        {
            if (entity)
            entity->destroy();
        }

        void cleanupDestroyedEntities()
        {
            m_Entities.erase(
                std::remove_if(
                    m_Entities.begin(),
                    m_Entities.end(),
                    [](const std::unique_ptr<Entity>& entity)
                    {
                        return entity->isDestroyed();
                    }
                ),
                m_Entities.end()
            );
        }

    private:
        std::uint32_t m_NextEntityID = 1;
        std::vector<std::unique_ptr<Entity>> m_Entities;

        MovementSystem m_MovementSystem;
        CameraFollowSystem m_CameraFollowSystem;
        RenderSystem m_RenderSystem;
        PlayerInputSystem m_PlayerInputSystem;
        TimerSystem m_TimerSystem;
    };

}