#pragma once
#include "Transform.hpp"
#include <string>

namespace Axiom {

    class Entity
    {
    public:
        Entity(const std::string& name = "Entity")
            : m_Name(name) {
        }

        Transform& getTransform()
        {
            return m_Transform;
        }

        const std::string& getName() const
        {
            return m_Name;
        }

    private:
        std::string m_Name;
        Transform m_Transform;
    };

}