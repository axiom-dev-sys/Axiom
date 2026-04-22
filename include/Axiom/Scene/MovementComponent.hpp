#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Component.hpp"
#include "Axiom/Scene/Transform.hpp"
#include "Axiom/Input/Input.hpp"



namespace Axiom {

    class MovementComponent : public Component
    {
    public:
        MovementComponent(Transform* transform, float speed = 2.0f)
            : m_Transform(transform), m_Speed(speed) {
        }

        void onUpdate() override
        {

        }

    private:
        Transform* m_Transform;
        float m_Speed;
    };

}