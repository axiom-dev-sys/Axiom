#pragma once
#include <glad/glad.h>

namespace Axiom {

    class Shader
    {
    public:
        static void init();
        static void use();
        static void setTransform(float x, float y, float sx, float sy);

    private:
        static GLuint program;
    };

}