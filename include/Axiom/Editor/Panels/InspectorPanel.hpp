#pragma once

#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Editor/EditorContext.hpp"

#include <string>
#include <cstdint>
#include <glm/glm.hpp>

namespace Axiom {

    class InspectorPanel
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        void setEntityName(const std::string& name)
        {
            entityName = name;
        }

        void setEntityID(std::uint32_t id)
        {
            entityID = id;
        }

        void setHasSprite(bool value);
        void setHasVelocity(bool value);
        void setHasCollider(bool value);
        void setHasPlayerController(bool value);
        void setHasPlayerTag(bool value);

        void setEditorContext(EditorContext* context);

    private:
        bool visible = true;

        std::string entityName = "None";
        std::uint32_t entityID = 0;

        bool hasSprite = false;
        bool hasVelocity = false;
        bool hasCollider = false;
        bool hasPlayerController = false;
        bool hasPlayerTag = false;

        char nameBuffer[256] = {};
        bool editingName = false;

        EditorContext* editorContext = nullptr;
    };

}