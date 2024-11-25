#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/logger.h"
#include "opengl_texture.h"
#include "CloudEngine/vec.h"
#include "opengl_mesh.h"
#include "CloudEngine/graphics/textures.h"

#include <cstdio>
#include <glad/gl.h>

void OGLMesh::Init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(fvec3),
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

        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(fvec2), &uvs.front(),
                     GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(1);
    }

    if (!normals.empty())
    {
        glGenBuffers(1, &nbo);
        glBindBuffer(GL_ARRAY_BUFFER, nbo);

        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(fvec3), &normals.front(), GL_STATIC_DRAW);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    nullTexture.filter = GL_NEAREST;
    nullTexture.CreateFromMemory(NULL_TEXTURE, 128, 128, 3);
}

void OGLMesh::Draw(Shader &shader)
{
    int numDiffuse = -1;
    int numSpecular = -1;
    for (int i = 0; i < textures.size(); i++)
    {
        static int index = 0;

        glActiveTexture(GL_TEXTURE0 + i);

        Texture texture = textures.at(i);

        std::string name;
        if (texture.type == TextureType::DIFFUSE)
        {
            numDiffuse++;
            name = "diffuse";
        }

        if (texture.type == TextureType::SPECULAR)
        {
            numSpecular++;
            name = "specular";
        }

        shader.SetVar("material." + name, i);

        if (numDiffuse > -1)
        {
            // shader.SetUniform("material.diffuse", i);
            // shader.SetUniform("material." + name + "[" + std::to_string(numDiffuse) + "]", i);
        }

        if (numSpecular > -1)
        {
            // shader.SetUniform("material.specular", i);
        }

        glBindTexture(GL_TEXTURE_2D, texture.id);
    }
    numDiffuse = -1;
    numSpecular = -1;

    if (textures.size() == 0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, nullTexture.id);

        shader.SetVar("material.diffuse", 0);
    }

    glBindVertexArray(vao);

    if (indices.empty())
    {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 3);
    }
    else
    {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
