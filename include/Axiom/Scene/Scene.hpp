#pragma once
#include "Entity.hpp"
#include "Axiom/Renderer/Camera.hpp"

#include <vector>
#include <memory>

namespace Axiom {

    class Scene
    {
    public:
        Camera camera;

        void onUpdate(float dt);

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

    private:
        std::vector<std::unique_ptr<Entity>> m_Entities;
    };

}