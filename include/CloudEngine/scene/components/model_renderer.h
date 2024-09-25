#pragma once

#include "CloudEngine/graphics/model.h"
#include "CloudEngine/scene/component.h"
#include <cstdio>

class ModelRenderer : public Component
{
public:
    inline void Init(std::string path)
    {
        this->model.Init(path);
    }

    inline Model &GetModel() { return this->model; }

private:
    Model model;
};
