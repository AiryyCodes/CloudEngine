#pragma once

#include "CloudEngine/core/graphics/model.h"
#include "CloudEngine/core/scene/component.h"

#include <cstdio>

class ModelRenderer : public Component
{
public:
    inline void Init(std::string path)
    {
        model.SetModel(path);
        model.Init();
    }

    std::unique_ptr<Component> CreateInstance() override { return std::make_unique<ModelRenderer>(); }

    Model &GetModel() { return this->model; }

private:
    Model model;
};
