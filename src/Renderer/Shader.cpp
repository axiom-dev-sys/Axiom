#include "Axiom/Renderer/Shader.hpp"

namespace Axiom {

    unsigned int Axiom::Shader::program = 0;

        const char* Shader::vs = R"(
#version 330 core
layout(location=0) in vec2 aPos;
layout(location=1) in vec2 aUV;
out vec2 vUV;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    vUV = aUV;
}
)";

        const char* Shader::fs = R"(
#version 330 core
in vec2 vUV;
out vec4 FragColor;
uniform sampler2D uTex;
void main() {
    FragColor = texture(uTex, vUV);
}
)";

        GLuint Shader::compile(GLenum type, const char* src)
        {
            GLuint s = glCreateShader(type);
            glShaderSource(s, 1, &src, nullptr);
            glCompileShader(s);
            return s;
        }

        void Shader::init()
        {
            GLuint v = compile(GL_VERTEX_SHADER, vs);
            GLuint f = compile(GL_FRAGMENT_SHADER, fs);

            program = glCreateProgram();
            glAttachShader(program, v);
            glAttachShader(program, f);
            glLinkProgram(program);

            glDeleteShader(v);
            glDeleteShader(f);

            glUseProgram(program);
            glUniform1i(glGetUniformLocation(program, "uTex"), 0);
        }

        void Shader::use()
        {
            glUseProgram(program);
        }

        void Shader::setInt(const char* name, int value)
        {
            glUseProgram(program);
            glUniform1i(glGetUniformLocation(program, name), value);
        }

}