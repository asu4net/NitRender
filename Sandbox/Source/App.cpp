#include "NitGraphics.h"
#include "Graphics/Material.h"

struct QuadVertex 
{
	glm::vec4 Position;
	glm::vec2 UVCoord;
	int       TextureSlot;
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
        layout(location = 1) in vec2 a_UVCoords;
        layout(location = 2) in int  a_TextureSlot;
        
        out vec2     v_UVCoords;
        flat out int v_TextureSlot;

        void main()
        {
            gl_Position   = a_Position;
            v_UVCoords    = a_UVCoords;
            v_TextureSlot = a_TextureSlot;
        }
    )";

const char* FragmentShaderSource = R"(        
        #version 410 core
        
        layout(location = 0) out vec4 color;
        
        uniform vec4      u_TintColor;
        uniform sampler2D u_TextureSlots[32];

        in vec2      v_UVCoords;
        flat in int  v_TextureSlot;

        void main()
        {
            color = texture(u_TextureSlots[v_TextureSlot], v_UVCoords) * u_TintColor;
        }
    )";

int main(int argc, char* argv[])
{
    Graphics::InitGraphics();

	auto VAO = Graphics::VertexArray::Create();
	auto VBO = Graphics::VertexBuffer::Create(sizeof(QuadVertex) * 4);
	
	VBO->SetLayout({
		{ Graphics::ShaderDataType::Float4, "a_Position"},
		{ Graphics::ShaderDataType::Float2, "a_UVCoords"},
		{ Graphics::ShaderDataType::Int,    "a_TextureSlot"}
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

    auto IBO = Graphics::IndexBuffer::Create(indices, maxIndices);
    delete[] indices;

    VAO->SetIndexBuffer(IBO);

    QuadVertex* quad = new QuadVertex[4];

    constexpr std::array<glm::vec4, 4> QuadVertexPos = {
        glm::vec4(-.5f, -.5f, 0, 1.f), // bottom-left
        glm::vec4( .5f, -.5f, 0, 1.f), // bottom-right
        glm::vec4( .5f,  .5f, 0, 1.f), // top-right
        glm::vec4(-.5f,  .5f, 0, 1.f)  // top-left
    };

    constexpr std::array<glm::vec2, 4> QuadUVCoords = {
        glm::vec2(0, 0), // bottom-left
        glm::vec2(1, 0), // bottom-right
        glm::vec2(1, 1), // top-right
        glm::vec2(0, 1)  // top-left
    };

    constexpr size_t MaxTextureSlots = 32;
    std::array<int32_t, MaxTextureSlots> textureSlots;
    for (size_t i = 0; i < MaxTextureSlots; ++i)
    {
        textureSlots[i] = i;
    }

    auto shader = Graphics::Shader::Create();
    shader->Compile(VertexShaderSource, FragmentShaderSource);
    
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
        Graphics::GetWindow().GetSize(&w, &h);
        const float aspect = static_cast<float>(w) / static_cast<float>(h);
        return aspect;
    };

    float nearClip = 0.1f;
    float farClip  = 1000.f;

    Graphics::Material material(shader);
    material.SetConstantVec4("u_TintColor", { 1, 1, 1, 1 });
    material.SetConstantSampler2D("u_TextureSlots[0]", &textureSlots.front(), MaxTextureSlots);
    
	while (Graphics::IsWindowOpened())
	{
        Graphics::ClearScreen();

        cameraTransform.Position.z -= 0.01f;
        cameraTransform.Position.x -= 0.005f;

        glm::mat4 proj = glm::perspective(glm::radians(fov), getAspect(), nearClip, farClip);
        glm::mat4 view = glm::inverse(cameraTransform.GetMatrix());

        for (uint32_t i = 0; i < 4; ++i)
        {
            quad[i].Position    = proj * view * spriteTransform.GetMatrix() *  QuadVertexPos[i];
            quad[i].UVCoord     = QuadUVCoords[i];
            quad[i].TextureSlot = 0;
        }

        VBO->SetData(quad, sizeof(QuadVertex) * 4);
        material.SubmitConstants();
        texture->Bind(0);
        Graphics::DrawElements(VAO, IBO->GetCount());
		Graphics::UpdateWindow();
	}

    Graphics::FinishGraphics();
}