#pragma once

#include "Axiom/Scene/Entity.hpp"

#include <vector>

namespace Axiom {

    class HierarchyPanel
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        void addEntity(Entity* entity);
        void clear();

        Entity* getSelectedEntity() const;

    private:
        bool visible = true;

        std::vector<Entity*> entities;

        Entity* selectedEntity = nullptr;
    };

}