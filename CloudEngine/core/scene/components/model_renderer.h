#pragma once

#include "CloudEngine/core/graphics/model.h"
#include "CloudEngine/core/scene/component.h"

#include <cstdio>

class ModelRenderer : public Component
{
public:
    void Init(std::string path);
    void Draw(Shader &shader) override;

    std::unique_ptr<Component> CreateInstance() override { return std::make_unique<ModelRenderer>(); }

    Model &GetModel() { return this->model; }

private:
    Model model;
};
