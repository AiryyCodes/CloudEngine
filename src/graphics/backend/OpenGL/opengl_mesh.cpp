#include "CloudEngine/graphics/mesh.h"

#include <cstdio>
#include <glad/gl.h>

void Mesh::Init()
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

    if (!indices.empty())
    {
        glGenBuffers(1, &ubo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ubo);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(unsigned int), &indices.front(),
                     GL_STATIC_DRAW);
    }

    if (!uvs.empty())
    {
        glGenBuffers(1, &tbo);
        glBindBuffer(GL_ARRAY_BUFFER, tbo);

        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), &uvs.front(),
                     GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(1);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::Draw()
{
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
