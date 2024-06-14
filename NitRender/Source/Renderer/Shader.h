#pragma once

namespace Nit
{
    class Shader;
    using ShaderPtr     = std::shared_ptr<Shader>;
    using ShaderWeakPtr = std::weak_ptr<Shader>;

    class Constant;
    using ConstantUniquePtr = std::unique_ptr<Constant>;

    //#TODO_asuarez Sería mejor pre-reservar memoria para todos los uniforms al principio para que esté más alineada y facilitar el acceso.
    // que el uniform se cree a sí mismo
    // hacer un getter de la data, o hacerla directamente pública
    // quitar el inútil weak ptr del shader
    // quizás habría que hacer que el material creara los uniforms al crearse, no el shader. Esto implicaría hacer una abstracción de Material por plataforma.
    // en ese caso mover todo esto al fichero Material.cpp
    // Al final Uniform va a ser un struct muy data oriented quizás...
    
    class Constant
    {
    public:
        static ConstantUniquePtr CreateUnique(const std::string& name, ShaderDataType type, int32_t size);

        Constant(const std::string& name, ShaderDataType type, int32_t size);
        Constant(Constant&& other) noexcept;
        Constant& operator=(Constant&& other) noexcept;

        ~Constant();

    private:
        union
        {
            void* m_Data = nullptr;
            int32_t* m_IntData;
            float* m_FloatData;
        };

        std::string    m_Name;
        ShaderDataType m_Type;
        int32_t        m_Size;
    };


    class Shader
    {
    public:
        static ShaderPtr Create();

        virtual void Compile(const char* vertexSource, const char* fragmentSource) = 0;
        
        virtual void GetConstantCollection(std::vector<ConstantUniquePtr>& constants) const = 0;
        virtual void SetConstantMat4(const char* constantName, const glm::mat4& mat) const = 0;
        virtual void SetConstantVec4(const char* constantName, const glm::vec4& vec) const = 0;
        virtual void SetConstantInt(const char* constantName, int num) = 0;
        virtual void SetConstantIntArray(const char* constantName, const int32_t* array, int32_t size) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
}