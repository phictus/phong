#include <glad/glad.h>
#include <stdio.h>

#include "renderer.h"
#include "matrix.h"

static uint32_t vao, vbo, ebo;
static uint32_t program, transformUniform, colorUniform;
static Mat4 transform;

static const char* vShaderSource =
"#version 450 core\n"
"\n"
"layout(location = 0) in vec3 a_Position;\n"
"\n"
"uniform mat4 u_Projection;\n"
"uniform mat4 u_Transform;\n"
"\n"
"void main()\n"
"{\n"
"   gl_Position = u_Projection * u_Transform * vec4(a_Position, 1.0);\n"
"}\n";
static const char* fShaderSource =
"#version 450 core\n"
"\n"
"layout(location = 0) out vec4 o_Color;\n"
"\n"
"uniform vec3 u_Color;\n"
"\n"
"void main()\n"
"{\n"
"   o_Color = vec4(u_Color, 1.0);\n"
"}\n";

void phInitRenderer()
{
    gladLoadGL();
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));

    uint32_t vShader, fShader;

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSource, NULL);
    glCompileShader(vShader);

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSource, NULL);
    glCompileShader(fShader);

    program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDetachShader(program, vShader);
    glDetachShader(program, fShader);
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    uint8_t indices[] = { 0, 2, 1, 0, 2, 3 };

    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glCreateBuffers(1, &ebo);

    glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glNamedBufferData(ebo, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float));
    glVertexArrayElementBuffer(vao, ebo);

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);

    Mat4 projection = phOrthographic(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    transform = phIdentity();

    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "u_Projection"), 1, GL_FALSE, projection.data);
    transformUniform = glGetUniformLocation(program, "u_Transform");
    colorUniform = glGetUniformLocation(program, "u_Color");
    glBindVertexArray(vao);
}

void phDestroyRenderer()
{
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
}

void phRenderRect(const Rect* rect, Color color)
{
    Vec3 position = { rect->x, rect->y, 0.0f };
    Vec3 scale = { rect->w, rect->h, 1.0f };
    phTranslate(&transform, &position);
    phScale(&transform, &scale);

    float r = 0.0f, g = 0.0f, b = 0.0f;
    switch (color)
    {
    case Yellow:
        r = 1.0f;
        g = 1.0f;
        break;
    case Red:
        r = 1.0f;
        break;
    case Blue:
        b = 1.0f;
        break;
    }

    glUniformMatrix4fv(transformUniform, 1, GL_FALSE, transform.data);
    glUniform3f(colorUniform, r, g, b);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
}
