#pragma once
#include "Texture2D.h"
#include "Material.h"

namespace Graphics
{
    struct Render2DInitArgs {};

    void InitRender2D(const Render2DInitArgs args = {});
    void NextBatch();
    void BeginRender2D(Material* material = nullptr, const glm::mat4& projection = glm::m4_identity);
    void SubmitSprite(const glm::mat4& transform, const Texture2DSPtr& texture = nullptr, const glm::vec4& tintColor = glm::v4_white);
    void EndRender2D();
    void FinishRender2D();
}