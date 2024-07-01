#pragma once

namespace Graphics
{
    class Shader;
    using ShaderSPtr    = std::shared_ptr<Shader>;

    class Constant;
    using ConstantUPtr = std::unique_ptr<Constant>;

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
        static ConstantUPtr CreateUnique(const std::string& name, ShaderDataType type, int32_t size);

        Constant(const std::string& name, ShaderDataType type, int32_t size);
        Constant(Constant&& other) noexcept;
        Constant& operator=(Constant&& other) noexcept;

        int32_t*             GetIntData()   const { return m_intData;   }
        float*               GetFloatData() const { return m_floatData; }
        const std::string&   GetName()      const { return m_name;      }
        ShaderDataType       GetType()      const { return m_type;      }
        int32_t              GetSize()      const { return m_size;      }

        ~Constant();

    private:
        union
        {
            void*    m_data = nullptr;
            int32_t* m_intData;
            float*   m_floatData;
        };

        std::string    m_name;
        ShaderDataType m_type;
        int32_t        m_size;
    };


    class Shader
    {
    public:
        static ShaderSPtr Create();

        virtual void Compile(const char* vertexSource, const char* fragmentSource) = 0;
        
        virtual void GetConstantCollection(std::vector<ConstantUPtr>& constants) const = 0;
        
        virtual void SetConstantFloat     (const char* name, float value)                        const = 0;
        virtual void SetConstantVec2      (const char* name, const float* value)                 const = 0;
        virtual void SetConstantVec3      (const char* name, const float* value)                 const = 0;
        virtual void SetConstantVec4      (const char* name, const float* value)                 const = 0;
        virtual void SetConstantMat4      (const char* name, const float* value)                 const = 0;
        virtual void SetConstantInt       (const char* name, int value)                          const = 0;
        virtual void SetConstantSampler2D (const char* name, const int32_t* value, int32_t size) const = 0;
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
}