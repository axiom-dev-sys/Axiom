#pragma once
#include "Entity.hpp"
#include <vector>

namespace Axiom {

    class Scene
    {
    public:
        Entity* createEntity(const std::string& name)
        {
            m_Entities.emplace_back(name);
            return &m_Entities.back();
        }

        std::vector<Entity>& getEntities()
        {
            return m_Entities;
        }

    private:
        std::vector<Entity> m_Entities;
    };

}