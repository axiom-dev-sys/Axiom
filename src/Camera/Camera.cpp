#include "Axiom/Camera/Camera.hpp"

namespace Axiom {

    void Camera::updateMatrix()
    {
        float left = position.x;
        float right = position.x + 1280;
        float bottom = position.y + 720;
        float top = position.y;

        m_Matrix[0] = 2.0f / (right - left);
        m_Matrix[5] = 2.0f / (top - bottom);
        m_Matrix[10] = -1.0f;
        m_Matrix[12] = -(right + left) / (right - left);
        m_Matrix[13] = -(top + bottom) / (top - bottom);
        m_Matrix[15] = 1.0f;
    }

}