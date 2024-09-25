#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/graphics/texture.h"

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

    if (!normals.empty())
    {
        glGenBuffers(1, &nbo);
        glBindBuffer(GL_ARRAY_BUFFER, nbo);

        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals.front(), GL_STATIC_DRAW);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(2);
    }

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader)
{
    unsigned int numDiffuse = -1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        Texture texture = textures.at(i);

        std::string name;
        if (texture.type == TextureType::DIFFUSE)
        {
            numDiffuse++;
            name = "diffuse";
        }

        if (numDiffuse > -1)
        {
            shader.SetUniform("material.diffuse", numDiffuse);
            // shader.SetUniform("material." + name + "[" + std::to_string(numDiffuse) + "]", i);
        }

        glBindTexture(GL_TEXTURE_2D, texture.id);
    }

    glBindVertexArray(vao);

    if (indices.empty())
    {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
    if (!indices.empty())
    {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
