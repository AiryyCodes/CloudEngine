#include "opengl_mesh.h"

#include <cstdio>
#include <glad/gl.h>

void OGLMesh::Init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 &vertices.front(), GL_STATIC_DRAW);

    // TODO: May be slow the way i am doing it, but idk?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OGLMesh::Draw()
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
