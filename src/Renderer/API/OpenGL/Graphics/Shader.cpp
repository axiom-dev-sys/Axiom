#include "Axiom/Renderer/Shader.hpp"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace Axiom {

    const char* Shader::vs = R"(
#version 330 core
layout(location=0) in vec2 aPos;
layout(location=1) in vec2 aTex;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 TexCoord;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPos, 0.0, 1.0);

    TexCoord = aTex;
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

        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        
        if (!success)
        {
            char log[512];
            glGetProgramInfoLog(program, 512, nullptr, log);
            std::cout << "Program link error:\n"
            << log << std::endl;
        }

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

    void Shader::setMat4(const char* name, const glm::mat4& value)
    {
        glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::setVec2(const char* name, float x, float y)
    {
        glUniform2f(glGetUniformLocation(program, name), x, y);
    }

}