#pragma once

namespace Graphics
{
    class Texture2D;
    class Material;

    struct Render2DInitArgs {};

    void Create2DRenderer(const Render2DInitArgs args = {});
    void StartBatch();
    void Flush();
    void NextBatch();
    void BeginRender2D(const glm::mat4& projection = glm::m4_identity, const std::shared_ptr<Material>& material = nullptr);
    void DrawQuad(const std::shared_ptr<Texture2D>& texture, const glm::mat4& transform = glm::m4_identity, const glm::vec4& tint = glm::v4_white);
    void EndRender2D();
    void Destroy2DRenderer();
}