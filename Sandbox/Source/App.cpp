#include "NitRender.h"

using namespace Nit;

struct QuadVertex 
{
	glm::vec4 Position;
};

struct Transform
{
    glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

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

constexpr uint32_t MaxPrimitives = 100;

const char* VertexShaderSource = R"(
        #version 410 core
        
        layout(location = 0) in vec4 a_Position;
        
        void main()
        {
            gl_Position = a_Position;
        }
    )";

const char* FragmentShaderSource = R"(        
        #version 410 core
        
        layout(location = 0) out vec4 color;
        
        void main()
        {
            color = vec4(1.f, 1.f, 1.f, 1.f);
        }
    )";

int main(int argc, char* argv[])
{
    auto window = Window::Create();

	auto VAO = VertexArray::Create();
	auto VBO = VertexBuffer::Create(sizeof(QuadVertex) * 4);
	
	VBO->SetLayout({
		{ ShaderDataType::Float4, "a_Position"}
	});

    VAO->AddVertexBuffer(VBO);

    constexpr uint32_t IndicesPerPrimitive = 6;
    const uint32_t maxIndices = MaxPrimitives * IndicesPerPrimitive;

    uint32_t* indices = new uint32_t[maxIndices];

    uint32_t offset = 0;

    for (uint32_t i = 0; i < maxIndices; i += 6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += 4;
    }

    auto IBO = IndexBuffer::Create(indices, maxIndices);
    delete[] indices;

    VAO->SetIndexBuffer(IBO);

    QuadVertex* quad = new QuadVertex[4];

    constexpr std::array<glm::vec4, 4> QuadVertexPos = {
            glm::vec4(-.5f, -.5f, 0, 1.f),
            glm::vec4( .5f, -.5f, 0, 1.f),
            glm::vec4( .5f,  .5f, 0, 1.f),
            glm::vec4(-.5f,  .5f, 0, 1.f)
    };

    auto shader = Shader::Create();
    shader->Compile(VertexShaderSource, FragmentShaderSource);
    
    auto renderAPI = RenderAPI::Create();
    renderAPI->SetClearColor({ .2f, .2f, .2f, 1 });
    renderAPI->SetBlendingEnabled(true);
    renderAPI->SetBlendingMode(BlendingMode::Alpha);
    renderAPI->SetDepthTestEnabled(true);

    Transform cameraTransform({0.f, 0.f, 5});
    Transform spriteTransform;

    float fov = 65;

    auto getAspect = [&window]() {
        int w, h;
        window->GetSize(&w, &h);
        const float aspect = static_cast<float>(w) / static_cast<float>(h);
        return aspect;
    };

    float nearClip = 0.1f;
    float farClip  = 1000.f;

	while (window->IsOpened())
	{
        renderAPI->Clear();

        cameraTransform.Position.z -= 0.01f;

        glm::mat4 proj = glm::perspective(glm::radians(fov), getAspect(), nearClip, farClip);
        glm::mat4 view = glm::inverse(cameraTransform.GetMatrix());

        for (uint32_t i = 0; i < 4; ++i)
        {
            quad[i].Position = proj * view * spriteTransform.GetMatrix() * QuadVertexPos[i];
        }

        VBO->SetData(quad, sizeof(QuadVertex) * 4);
        shader->Bind();
        renderAPI->DrawElements(VAO, IBO->GetCount());
		window->Update();
	}
}