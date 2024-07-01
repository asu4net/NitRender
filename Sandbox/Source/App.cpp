#include "NitGraphicsPCH.h"
#include "Graphics\Graphics.h"
#include "Graphics\Renderer2D.h"
#include "Display\Display.h"
#include "Graphics\Texture2D.h"

struct Transform
{
    glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Scale    = { 1.0f, 1.0f, 1.0f };

    Transform() = default;
    Transform(const Transform&) = default;
    Transform(const glm::vec3& translation)
        : Position(translation) {}

    glm::mat4 GetMatrix() const
    {
        glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

        return glm::translate(glm::mat4(1.0f), Position)
            * rotation
            * glm::scale(glm::mat4(1.0f), Scale);
    }
};

int main(int argc, char* argv[])
{
    Graphics::CreateGraphicsContext();
    Display::CreateWindow();
    Graphics::InitRender2D();

    auto texture = Graphics::Texture2D::Create();
    Graphics::Image image("Assets/Cpp.png");
    texture->UploadToGPU(image);
    image.Free();

    Graphics::SetClearColor({ .2f, .2f, .2f, 1 });
    Graphics::SetBlendingEnabled(true);
    Graphics::SetBlendingMode(Graphics::BlendingMode::Alpha);
    Graphics::SetDepthTestEnabled(true);

    Transform cameraTransform({0.f, 0.f, 5});
    Transform spriteTransform;

    float fov = 65;

    auto getAspect = []() {
        int w, h;
        Display::GetWindow().GetSize(&w, &h);
        const float aspect = static_cast<float>(w) / static_cast<float>(h);
        return aspect;
    };

    float nearClip = 0.1f;
    float farClip  = 1000.f;

	while (Display::IsWindowOpened())
	{
        Graphics::ClearScreen();

        cameraTransform.Position.z -= 0.01f;
        cameraTransform.Position.x -= 0.005f;

        glm::mat4 proj = glm::perspective(glm::radians(fov), getAspect(), nearClip, farClip);
        glm::mat4 view = glm::inverse(cameraTransform.GetMatrix());

        Graphics::BeginRender2D(proj * view);
        Graphics::DrawQuad(texture, spriteTransform.GetMatrix());
        Graphics::EndRender2D();

        Display::UpdateWindow();
	}

    Graphics::FinishRender2D();
    Display::DestroyWindow();
    Graphics::DestroyGraphicsContext();
}