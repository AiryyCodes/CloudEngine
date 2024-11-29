#include "CloudEngine/core/scene/components/model_renderer.h"

void ModelRenderer::Init(std::string path)
{
    model.SetModel(path);
    model.Init();
}

void ModelRenderer::Draw(Shader &shader)
{
    model.Draw(shader);
}
