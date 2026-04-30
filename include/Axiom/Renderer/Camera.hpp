#pragma once
#include "Axiom/Math/Vec2.hpp"

namespace Axiom {

    class Camera {
    public:
        Vec2 position{ 0, 0 };

        void updateMatrix();

        const float* getMatrix() const { return m_Matrix; }

    private:
        float m_Matrix[16] = { 0 };
    };

}