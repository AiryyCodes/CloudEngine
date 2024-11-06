#pragma once

#include "CloudEngine/graphics/model.h"
#include "CloudEngine/scene/component.h"
#include <cstdio>

class ModelRenderer : public Component
{
public:
    inline void Init(std::string path)
    {
        model.SetModel(path);
        model.Init();
    }

    Model &GetModel() { return this->model; }

private:
    Model model;
};
