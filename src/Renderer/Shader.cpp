#include "Axiom/Renderer/Shader.hpp"
#include <iostream>

namespace Axiom {

    const char* Shader::vs = R"(
#version 330 core
layout(location=0) in vec2 aPos;
layout(location=1) in vec2 aUV;
out vec2 vUV;
uniform mat4 uProjection;
void main() {
    gl_Position = uProjection * vec4(aPos, 0.0, 1.0);
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

        GLint success;
        glGetShaderiv(s, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            char log[512];
            glGetShaderInfoLog(s, 512, nullptr, log);
            std::cout << "Shader compile error:\n" << log << std::endl;
        }

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

        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success)
        {
            char log[512];
            glGetProgramInfoLog(program, 512, nullptr, log);
            std::cout << "Shader link error:\n" << log << std::endl;
        }

        glDeleteShader(v);
        glDeleteShader(f);

        glUseProgram(program);
    }

    void Shader::use()
    {
        glUseProgram(program);
    }

    void Shader::setInt(const char* name, int value)
    {
        glUniform1i(glGetUniformLocation(program, name), value);
    }

    void Shader::setMat4(const char* name, const float* value)
    {
        glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, value);
    }

}