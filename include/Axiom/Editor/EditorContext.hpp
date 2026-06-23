#pragma once

#include "Axiom/Scene/Entity.hpp"

namespace Axiom {

    class EditorContext
    {
    public:
        Entity* getSelectedEntity() const;
        void setSelectedEntity(Entity* entity);
        void clearSelection();

    private:
        Entity* selectedEntity = nullptr;
    };

}