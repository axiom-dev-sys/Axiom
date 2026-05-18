#include "Axiom/Renderer/Shader.hpp"
#include <iostream>

namespace Axiom {

    const char* Shader::vs = R"(
#version 330 core
layout(location=0) in vec2 aPos;
layout(location=1) in vec2 aUV;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    TexCoord = aUV;
}
)";

    const char* Shader::fs = R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D uTex;

void main() {
    FragColor = texture(uTex, TexCoord);
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

        GLuint vsID = compile(GL_VERTEX_SHADER, vs);
        GLuint fsID = compile(GL_FRAGMENT_SHADER, fs);

        program = glCreateProgram();
        glAttachShader(program, vsID);
        glAttachShader(program, fsID);
        glLinkProgram(program);

        glDeleteShader(vsID);
        glDeleteShader(fsID);

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

    void Shader::setVec2(const char* name, float x, float y)
    {
        glUniform2f(glGetUniformLocation(program, name), x, y);
    }

}