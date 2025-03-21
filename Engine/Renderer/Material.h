#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Texture.h"
#include "Engine/Vector.h"

class Material
{
public:
    Material()
        : m_Color({1.0f, 1.0f, 1.0f, 1.0f}), m_Texture(nullptr) {}
    Material(const Vector4f &color)
        : m_Color(color), m_Texture(nullptr) {}
    Material(const Ref<Texture> &texture)
        : m_Texture(texture) {}

    Ref<Texture> GetTexture() const { return m_Texture; }
    void SetTexture(const Ref<Texture> &texture) { m_Texture = texture; }

    Vector4f GetColor() const { return m_Color; }
    void SetColor(const Vector4f &color) { m_Color = color; }

private:
    Ref<Texture> m_Texture;

    Vector4f m_Color;
};
