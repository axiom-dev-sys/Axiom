#pragma once
#include "Component.hpp"
#include "Transform.hpp"



namespace Axiom {

    class ColliderComponent : public Component
    {
    public:
        ColliderComponent(Transform* transform, float width = 1.0f, float height = 1.0f)
            : m_Transform(transform), m_Width(width), m_Height(height) {
        }

        float getLeft()   const { return m_Transform->x - m_Width / 2.0f; }
        float getRight()  const { return m_Transform->x + m_Width / 2.0f; }
        float getTop()    const { return m_Transform->y + m_Height / 2.0f; }
        float getBottom() const { return m_Transform->y - m_Height / 2.0f; }

    private:
        Transform* m_Transform;
        float m_Width;
        float m_Height;
    };

}