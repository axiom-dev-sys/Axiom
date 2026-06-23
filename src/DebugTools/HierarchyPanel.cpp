#include "Axiom/DebugTools/HierarchyPanel.hpp"

#include <imgui.h>
#include <string>

namespace Axiom {

    void HierarchyPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Hierarchy");

        for (Entity* entity : entities)
        {
            if (!entity)
                continue;

            if (entity->isDestroyed())
                continue;

            bool selected = (entity == selectedEntity);

            std::string label =
                entity->getName() + "##" + std::to_string(entity->getID());

            if (ImGui::Selectable(label.c_str(), selected))
            {
                selectedEntity = entity;
            }
        }

        ImGui::End();
    }

    void HierarchyPanel::setVisible(bool value)
    {
        visible = value;
    }

    bool HierarchyPanel::isVisible() const
    {
        return visible;
    }

    void HierarchyPanel::toggle()
    {
        visible = !visible;
    }

    void HierarchyPanel::addEntity(Entity* entity)
    {
        if (!entity)
            return;

        entities.push_back(entity);
    }

    void HierarchyPanel::clear()
    {
        entities.clear();
    }

    Entity* HierarchyPanel::getSelectedEntity() const
    {
        return selectedEntity;
    }

    void HierarchyPanel::clearSelection()
    {
        selectedEntity = nullptr;
    }

}