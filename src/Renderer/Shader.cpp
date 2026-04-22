#include "Axiom/Renderer/Shader.hpp"
#include <iostream>

namespace Axiom {

    GLuint Shader::program = 0;

    static const char* vs = R"(
#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;

uniform vec2 uPos;
uniform vec2 uScale;

out vec2 vUV;

void main()
{
    vec2 pos = aPos * uScale + uPos;
    gl_Position = vec4(pos, 0.0, 1.0);
    vUV = aUV;
}
)";

    static const char* fs = R"(
#version 330 core

out vec4 FragColor;
in vec2 vUV;

uniform sampler2D uTex;

void main()
{
    FragColor = texture(uTex, vUV);
}
)";

    static GLuint compile(GLenum type, const char* src)
    {
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);

        int ok;
        glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
        if (!ok)
        {
            char log[512];
            glGetShaderInfoLog(s, 512, nullptr, log);
            std::cout << "Shader error: " << log << std::endl;
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

        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success)
        {
            char log[512];
            glGetProgramInfoLog(program, 512, nullptr, log);
            std::cout << "PROGRAM LINK ERROR: " << log << std::endl;
        }

        glDeleteShader(v);
        glDeleteShader(f);

        glUseProgram(program);
        glUniform1i(glGetUniformLocation(program, "uTex"), 0);
    }

    void Shader::use()
    {
        glUseProgram(program);
    }

    void Shader::setTransform(float x, float y, float sx, float sy)
    {
        glUseProgram(program);

        glUniform2f(glGetUniformLocation(program, "uPos"), 0.0f, 0.0f);
        glUniform2f(glGetUniformLocation(program, "uScale"), 2.0f, 2.0f);
    }

}