#pragma once

#include "CloudEngine/core/graphics/mesh.h"
#include "CloudEngine/core/graphics/texture.h"
#include "CloudEngine/core/scene/component.h"

#include <memory>

class SpriteRenderer : public Component
{
public:
    void Init() override;
    void Draw(Shader &shader) override;

    void Init(std::string path);

    const Texture &GetSprite() const { return sprite; }

private:
    Texture sprite;
    std::unique_ptr<Mesh> mesh;
};
